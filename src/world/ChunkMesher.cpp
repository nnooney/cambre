////////////////////////////////////////////////////////////////////////////////
/// @file ChunkMesher.cpp
/// @brief A mesher for the chunk class.
///
/// This file implements the Mesh Interface provided for the Chunk Class.
////////////////////////////////////////////////////////////////////////////////

#include "ChunkMesher.hpp"

ChunkMesher::ChunkMesher(void)
{
    mVao = 0;
    mVbo = 0;
}

ChunkMesher::~ChunkMesher(void)
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

void ChunkMesher::allocateBuffers(void)
{
    glGenVertexArrays(1, &mVao);
    glBindVertexArray(mVao);

    glGenBuffers(1, &mVbo);
}

void ChunkMesher::generate(uint8_t aData[16][16][16], int size)
{
    // Perform Meshing to generate the buffer data needed to render the chunk.
    // Currently this uses a naive implementation of meshing; eventually, it
    // will be updated to use greedy meshing.
    // https://0fps.net/2012/06/30/meshing-in-a-minecraft-game/

    // The naive meshing implementation will generate 36 vertices for each voxel
    // that is not empty.
    mMeshData.clear();
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            for (int z = 0; z < size; z++)
            {
                uint8_t type = aData[x][y][z];

                // Do not add vertices for empty blocks.
                if (type == 0)
                {
                    continue;
                }

                // Add the 36 vertices to the mesh data.

                // Negative X
                addTriangleToMesh(x,   y,   z,   type);
                addTriangleToMesh(x,   y,   z+1, type);
                addTriangleToMesh(x,   y+1, z+1, type);
                addTriangleToMesh(x,   y,   z,   type);
                addTriangleToMesh(x,   y+1, z+1, type);
                addTriangleToMesh(x,   y+1, z,   type);

                // Positive X
                addTriangleToMesh(x+1, y,   z,   type);
                addTriangleToMesh(x+1, y+1, z,   type);
                addTriangleToMesh(x+1, y+1, z+1, type);
                addTriangleToMesh(x+1, y,   z,   type);
                addTriangleToMesh(x+1, y+1, z+1, type);
                addTriangleToMesh(x+1, y,   z+1, type);

                // Negative Y
                addTriangleToMesh(x,   y,   z,   type);
                addTriangleToMesh(x+1, y,   z,   type);
                addTriangleToMesh(x+1, y,   z+1, type);
                addTriangleToMesh(x,   y,   z,   type);
                addTriangleToMesh(x+1, y,   z+1, type);
                addTriangleToMesh(x,   y,   z+1, type);

                // Positive Y
                addTriangleToMesh(x,   y+1, z,   type);
                addTriangleToMesh(x,   y+1, z+1, type);
                addTriangleToMesh(x+1, y+1, z+1, type);
                addTriangleToMesh(x,   y+1, z,   type);
                addTriangleToMesh(x+1, y+1, z+1, type);
                addTriangleToMesh(x+1, y+1, z,   type);

                // Negative Z
                addTriangleToMesh(x,   y,   z,   type);
                addTriangleToMesh(x,   y+1, z,   type);
                addTriangleToMesh(x+1, y+1, z,   type);
                addTriangleToMesh(x,   y,   z,   type);
                addTriangleToMesh(x+1, y+1, z,   type);
                addTriangleToMesh(x+1, y,   z,   type);

                // Positive Z
                addTriangleToMesh(x,   y,   z+1, type);
                addTriangleToMesh(x+1, y,   z+1, type);
                addTriangleToMesh(x+1, y+1, z+1, type);
                addTriangleToMesh(x,   y,   z+1, type);
                addTriangleToMesh(x+1, y+1, z+1, type);
                addTriangleToMesh(x,   y+1, z+1, type);
            }
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBufferData(GL_ARRAY_BUFFER, mMeshData.size() * sizeof(GLbyte),
        mMeshData.data(), GL_STATIC_DRAW);
}

void ChunkMesher::render(void)
{
    if (mMeshData.size() == 0)
    {
        return;
    }

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glVertexAttribPointer(0, 4, GL_BYTE, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, mMeshData.size());

    glDisableVertexAttribArray(0);
}

void ChunkMesher::addTriangleToMesh(int x, int y, int z, int type)
{
    mMeshData.push_back(x);
    mMeshData.push_back(y);
    mMeshData.push_back(z);
    mMeshData.push_back(type);
}
