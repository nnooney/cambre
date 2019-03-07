////////////////////////////////////////////////////////////////////////////////
/// @file Chunk.cpp
/// @brief A Class to store several blocks.
///
/// This file contains the Chunk class. It contains several blocks, and it is
/// responsible for rendering all the blocks via one call.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "Chunk.hpp"

Chunk::Chunk(void)
{
    mVao = 0;
    mVbo = 0;
    mUpdateRequired = true;
    mx = my = mz = 0;

    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int y = 0; y < CHUNK_SIZE; y++)
        {
            for (int z = 0; z < CHUNK_SIZE; z++)
            {
                mBlocks[x][y][z] =
                    ((x % 2 == 0) && (y % 2 == 0) && (z % 2 == 0)) ? 1 : 0;
            }
        }
    }
}

Chunk::Chunk(int x, int y, int z) : mx(x), my(y), mz(z)
{
    mVao = 0;
    mVbo = 0;
    mUpdateRequired = true;

    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int y = 0; y < CHUNK_SIZE; y++)
        {
            for (int z = 0; z < CHUNK_SIZE; z++)
            {
                mBlocks[x][y][z] =
                    ((x % 2 == 0) && (y % 2 == 0) && (z % 2 == 0)) ? 1 : 0;
            }
        }
    }
}

Chunk::~Chunk(void)
{
    if (mVao != 0)
    {
        glDeleteVertexArrays(1, &mVao);
    }

    if (mVbo != 0)
    {
        glDeleteBuffers(1, &mVbo);
    }
}

void Chunk::initialize(void)
{
    glGenVertexArrays(1, &mVao);
    glBindVertexArray(mVao);

    glGenBuffers(1, &mVbo);
}

void Chunk::update(void)
{
    if (!mUpdateRequired)
    {
        return;
    }
    mUpdateRequired = false;

    // Perform Meshing to generate the buffer data needed to render the chunk.
    // Currently this uses a naive implementation of meshing; eventually, it
    // will be updated to use greedy meshing.
    // https://0fps.net/2012/06/30/meshing-in-a-minecraft-game/

    // The naive meshing implementation will generate 36 vertices for each voxel
    // that is not empty.
    int i = 0;
    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int y = 0; y < CHUNK_SIZE; y++)
        {
            for (int z = 0; z < CHUNK_SIZE; z++)
            {
                uint8_t type = mBlocks[x][y][z];

                // Do not add vertices for empty blocks.
                if (type == 0)
                {
                    continue;
                }

                // Add the 36 vertices to the mesh data.

                // Negative X
                mMeshData[i++] = glm::tvec4<GLbyte>(x,   y,   z,   type);
                mMeshData[i++] = glm::tvec4<GLbyte>(x,   y,   z+1, type);
                mMeshData[i++] = glm::tvec4<GLbyte>(x,   y+1, z+1, type);
                mMeshData[i++] = glm::tvec4<GLbyte>(x,   y,   z,   type);
                mMeshData[i++] = glm::tvec4<GLbyte>(x,   y+1, z+1, type);
                mMeshData[i++] = glm::tvec4<GLbyte>(x,   y+1, z,   type);

                // Positive X
                mMeshData[i++] = glm::tvec4<GLbyte>(x+1, y,   z,   type);
                mMeshData[i++] = glm::tvec4<GLbyte>(x+1, y+1, z,   type);
                mMeshData[i++] = glm::tvec4<GLbyte>(x+1, y+1, z+1, type);
                mMeshData[i++] = glm::tvec4<GLbyte>(x+1, y,   z,   type);
                mMeshData[i++] = glm::tvec4<GLbyte>(x+1, y+1, z+1, type);
                mMeshData[i++] = glm::tvec4<GLbyte>(x+1, y,   z+1, type);

                // Negative Y
                mMeshData[i++] = glm::tvec4<GLbyte>(x,   y,   z,   type);
                mMeshData[i++] = glm::tvec4<GLbyte>(x+1, y,   z,   type);
                mMeshData[i++] = glm::tvec4<GLbyte>(x+1, y,   z+1, type);
                mMeshData[i++] = glm::tvec4<GLbyte>(x,   y,   z,   type);
                mMeshData[i++] = glm::tvec4<GLbyte>(x+1, y,   z+1, type);
                mMeshData[i++] = glm::tvec4<GLbyte>(x,   y,   z+1, type);

                // Positive Y
                mMeshData[i++] = glm::tvec4<GLbyte>(x,   y+1, z,   type);
                mMeshData[i++] = glm::tvec4<GLbyte>(x,   y+1, z+1, type);
                mMeshData[i++] = glm::tvec4<GLbyte>(x+1, y+1, z+1, type);
                mMeshData[i++] = glm::tvec4<GLbyte>(x,   y+1, z,   type);
                mMeshData[i++] = glm::tvec4<GLbyte>(x+1, y+1, z+1, type);
                mMeshData[i++] = glm::tvec4<GLbyte>(x+1, y+1, z,   type);

                // Negative Z
                mMeshData[i++] = glm::tvec4<GLbyte>(x,   y,   z,   type);
                mMeshData[i++] = glm::tvec4<GLbyte>(x,   y+1, z,   type);
                mMeshData[i++] = glm::tvec4<GLbyte>(x+1, y+1, z,   type);
                mMeshData[i++] = glm::tvec4<GLbyte>(x,   y,   z,   type);
                mMeshData[i++] = glm::tvec4<GLbyte>(x+1, y+1, z,   type);
                mMeshData[i++] = glm::tvec4<GLbyte>(x+1, y,   z,   type);

                // Positive Z
                mMeshData[i++] = glm::tvec4<GLbyte>(x,   y,   z+1, type);
                mMeshData[i++] = glm::tvec4<GLbyte>(x+1, y,   z+1, type);
                mMeshData[i++] = glm::tvec4<GLbyte>(x+1, y+1, z+1, type);
                mMeshData[i++] = glm::tvec4<GLbyte>(x,   y,   z+1, type);
                mMeshData[i++] = glm::tvec4<GLbyte>(x+1, y+1, z+1, type);
                mMeshData[i++] = glm::tvec4<GLbyte>(x,   y+1, z+1, type);
            }
        }
    }

    mMeshElements = i;
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBufferData(GL_ARRAY_BUFFER, mMeshElements * sizeof(*mMeshData), mMeshData,
        GL_STATIC_DRAW);
}

void Chunk::render(void)
{
    if (mMeshElements == 0)
    {
        return;
    }

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glVertexAttribPointer(0, 4, GL_BYTE, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, mMeshElements);

    glDisableVertexAttribArray(0);
}
