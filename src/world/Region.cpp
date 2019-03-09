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
    mChunks.insert({glm::ivec3(0, 0, 0), new Chunk(0, 0, 0)});
    mChunks.insert({glm::ivec3(1, 0, 0), new Chunk(1, 0, 0)});
    mChunks.insert({glm::ivec3(0, 0, 1), new Chunk(0, 0, 1)});
    mChunks.insert({glm::ivec3(1, 0, 1), new Chunk(1, 0, 1)});
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
        p.second->update();
    }
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
