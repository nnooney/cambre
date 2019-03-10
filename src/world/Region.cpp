////////////////////////////////////////////////////////////////////////////////
/// @file Region.cpp
/// @brief A class to handle multiple chunks.
///
/// This file contains the Region class. Multiple chunks get organized into a
/// region. The region is responsible for maintaining the list of chunks as well
/// as loading and unloading the chunks.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Region.hpp"

Region::Region(void)
{
    mChunkDistance = 64;
    mChunkLoadRate = 10;
    mChunkUnloadRate = 10;

    mChunks.insert({glm::ivec3(0, 0, 0), new Chunk(0, 0, 0)});
}

Region::~Region(void)
{
    for (std::pair<glm::ivec3, Chunk *> p : mChunks)
    {
        if (p.second != nullptr)
        {
            delete p.second;
        }
    }
}

void Region::initialize(void)
{
    mUniformVP = mShaderProgram.getUniformLocation("ViewProjection");
    mUniformModel = mShaderProgram.getUniformLocation("Model");

    for (std::pair<glm::ivec3, Chunk *> p : mChunks)
    {
        p.second->initialize();
    }
}

void Region::update(void)
{
    mCameraController.update();

    for (std::pair<glm::ivec3, Chunk *> p : mChunks)
    {
        // Check if the chunk has neighbors that need to be loaded.
        if (p.second->getNumNeighbors() < 6)
        {
            // If not all the neighbors are loaded, then either this chunk needs
            // to be unloaded or its neighbors need to be loaded.
            updateChunkLists(p);
        }

        // Update the Chunk
        p.second->update();
    }

    // Add and Remove Chunks from the hashmap.
    unloadChunks();
    loadChunks();

}

void Region::render(void)
{
    glm::mat4 view = mCameraController.getView();
    glm::mat4 proj = glm::perspective(
        glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
    glUniformMatrix4fv(mUniformVP, 1, GL_FALSE, glm::value_ptr(proj * view));

    for (std::pair<glm::ivec3, Chunk *> p : mChunks)
    {
        // Update the Model Matrix to position the chunk in the world.
        glm::mat4 model = glm::translate(
            glm::mat4(1),
            glm::vec3(
                p.first.x * Chunk::CHUNK_SIZE,
                p.first.y * Chunk::CHUNK_SIZE,
                p.first.z * Chunk::CHUNK_SIZE));

        // Set the Model Matrix Uniform.
        glUniformMatrix4fv(mUniformModel, 1, GL_FALSE, glm::value_ptr(model));

        p.second->render();
    }
}

void Region::useShader(ShaderProgram &shader)
{
    // Ensure that the shader is ready to be used.
    if (shader.isReadyToUse() != true)
    {
        std::cerr << "Region::useShader Shader is not ready to use"
            << std::endl;
        return;
    }

    // Save the shader reference being used.
    mShaderProgram = shader;

    // Indicate that the program is being used for OpenGL.
    mShaderProgram.use();
}

void Region::useCameraController(CameraController &cc)
{
    mCameraController = cc;
}

void Region::registerWith(InputManager &manager)
{
    mCameraController.registerWith(manager);
}

void Region::updateChunkLists(std::pair<glm::ivec3, Chunk*> ci)
{
    // The algorithm for updating the chunkmap is as follows:
    // 1. Check if the chunk should be unloaded. If it is, add it to the list of
    //    chunks to unload and return.
    // 2. If the chunk shouldn't be unloaded, then check if each of its
    //    neighbors to determine if they should be loaded.
    // Note that this function does not actually add/remove chunks from the map;
    // instead, it only updates the lists of chunks to load and unload.

    // The chunk load algorithm returns true if a chunk should be loaded and
    // false if it should not be loaded.
    if (!chunkLoadAlgorithm(ci.first))
    {
        mChunkRemoveList.push(ci.first);
        return;
    }

    // If the chunk should be loaded, then check its neighbors to determine if
    // they should also be loaded.
    if (!(ci.second->hasNeighbor(Chunk::pX)) &&
        chunkLoadAlgorithm(ci.first + glm::ivec3(1.0, 0.0, 0.0)))
    {
        mChunkLoadList.push(ci.first + glm::ivec3(1.0, 0.0, 0.0));
    }

    if (!(ci.second->hasNeighbor(Chunk::nX)) &&
        chunkLoadAlgorithm(ci.first + glm::ivec3(-1.0, 0.0, 0.0)))
    {
        mChunkLoadList.push(ci.first + glm::ivec3(-1.0, 0.0, 0.0));
    }

    if (!(ci.second->hasNeighbor(Chunk::pY)) &&
        chunkLoadAlgorithm(ci.first + glm::ivec3(0.0, 1.0, 0.0)))
    {
        mChunkLoadList.push(ci.first + glm::ivec3(0.0, 1.0, 0.0));
    }

    if (!(ci.second->hasNeighbor(Chunk::nY)) &&
        chunkLoadAlgorithm(ci.first + glm::ivec3(0.0, -1.0, 0.0)))
    {
        mChunkLoadList.push(ci.first + glm::ivec3(0.0, -1.0, 0.0));
    }

    if (!(ci.second->hasNeighbor(Chunk::pZ)) &&
        chunkLoadAlgorithm(ci.first + glm::ivec3(0.0, 0.0, 1.0)))
    {
        mChunkLoadList.push(ci.first + glm::ivec3(0.0, 0.0, 1.0));
    }

    if (!(ci.second->hasNeighbor(Chunk::nZ)) &&
        chunkLoadAlgorithm(ci.first + glm::ivec3(0.0, 0.0, -1.0)))
    {
        mChunkLoadList.push(ci.first + glm::ivec3(0.0, 0.0, -1.0));
    }
}

bool Region::chunkLoadAlgorithm(glm::ivec3 coords)
{
    // Use the camera's distance from the center of the chunk to determine if
    // it should be loaded or not.
    glm::vec3 cameraPos = mCameraController.getPosition();
    glm::vec3 chunkWorldPos = Chunk::chunkCenterToWorldCoords(coords);

    return (glm::distance(cameraPos, chunkWorldPos) < mChunkDistance);
}

void Region::loadChunks(void)
{
    unsigned int chunkCounter = 0;

    while ((mChunkLoadList.size() > 0) && (chunkCounter < mChunkLoadRate))
    {
        glm::ivec3 coords = mChunkLoadList.front();

        // Prevent duplicate loads.
        if (mChunks.find(coords) != mChunks.end())
        {
            mChunkLoadList.pop();
            continue;
        }

        Chunk *c = new Chunk(coords.x, coords.y, coords.z);

        // Connect the neighbors.
        auto npx = mChunks.find(coords + glm::ivec3(1.0, 0.0, 0.0));
        if (npx != mChunks.end())
        {
            npx->second->setNeighbor(Chunk::nX, c);
            c->setNeighbor(Chunk::pX, npx->second);
        }

        auto nnx = mChunks.find(coords + glm::ivec3(-1.0, 0.0, 0.0));
        if (nnx != mChunks.end())
        {
            nnx->second->setNeighbor(Chunk::pX, c);
            c->setNeighbor(Chunk::nX, nnx->second);
        }

        auto npy = mChunks.find(coords + glm::ivec3(0.0, 1.0, 0.0));
        if (npy != mChunks.end())
        {
            npy->second->setNeighbor(Chunk::nY, c);
            c->setNeighbor(Chunk::pY, npy->second);
        }

        auto nny = mChunks.find(coords + glm::ivec3(0.0, -1.0, 0.0));
        if (nny != mChunks.end())
        {
            nny->second->setNeighbor(Chunk::pY, c);
            c->setNeighbor(Chunk::nY, nny->second);
        }

        auto npz = mChunks.find(coords + glm::ivec3(0.0, 0.0, 1.0));
        if (npz != mChunks.end())
        {
            npz->second->setNeighbor(Chunk::nZ, c);
            c->setNeighbor(Chunk::pZ, npz->second);
        }

        auto nnz = mChunks.find(coords + glm::ivec3(0.0, 0.0, -1.0));
        if (nnz != mChunks.end())
        {
            nnz->second->setNeighbor(Chunk::pZ, c);
            c->setNeighbor(Chunk::nZ, nnz->second);
        }

        c->initialize();
        mChunks.insert({coords, c});

        mChunkLoadList.pop();
        chunkCounter++;
    }
}

void Region::unloadChunks(void)
{
    unsigned int chunkCounter = 0;

    while ((mChunkRemoveList.size() > 0) && (chunkCounter < mChunkUnloadRate))
    {
        glm::ivec3 coords = mChunkRemoveList.front();

        // Prevent duplicate unloads.
        if (mChunks.find(coords) == mChunks.end())
        {
            mChunkRemoveList.pop();
            continue;
        }

        Chunk *c = mChunks.at(coords);

        // Disconnect the neighbors.
        if (c->hasNeighbor(Chunk::pX))
        {
            c->getNeighbor(Chunk::pX)->setNeighbor(Chunk::nX, nullptr);
        }

        if (c->hasNeighbor(Chunk::nX))
        {
            c->getNeighbor(Chunk::nX)->setNeighbor(Chunk::pX, nullptr);
        }

        if (c->hasNeighbor(Chunk::pY))
        {
            c->getNeighbor(Chunk::pY)->setNeighbor(Chunk::nY, nullptr);
        }

        if (c->hasNeighbor(Chunk::nY))
        {
            c->getNeighbor(Chunk::nY)->setNeighbor(Chunk::pY, nullptr);
        }

        if (c->hasNeighbor(Chunk::pZ))
        {
            c->getNeighbor(Chunk::pZ)->setNeighbor(Chunk::nZ, nullptr);
        }

        if (c->hasNeighbor(Chunk::nZ))
        {
            c->getNeighbor(Chunk::nZ)->setNeighbor(Chunk::pZ, nullptr);
        }

        delete c;
        mChunks.erase(coords);

        mChunkRemoveList.pop();
        chunkCounter++;
    }
}
