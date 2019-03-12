////////////////////////////////////////////////////////////////////////////////
/// @file Chunk.cpp
/// @brief A Class to store several blocks.
///
/// This file contains the Chunk class. It contains several blocks, and it is
/// responsible for rendering all the blocks via one call.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "CheckError.hpp"
#include "Chunk.hpp"

Chunk::Chunk(void)
{
    mUpdateRequired = true;
    mNeighbors = {0};
    mx = my = mz = 0;

    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int y = 0; y < CHUNK_SIZE; y++)
        {
            for (int z = 0; z < CHUNK_SIZE; z++)
            {
                if (my > 0)
                {
                    mBlocks[x][y][z] = 0;
                    continue;
                }

                mBlocks[x][y][z] =
                    ((x % 2 == 0) && (y % 2 == 0) && (z % 2 == 0)) ? 1 : 0;
            }
        }
    }
}

Chunk::Chunk(int x, int y, int z) : mx(x), my(y), mz(z)
{
    mUpdateRequired = true;
    mNeighbors = {0};

    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int y = 0; y < CHUNK_SIZE; y++)
        {
            for (int z = 0; z < CHUNK_SIZE; z++)
            {
                if (my > 0)
                {
                    mBlocks[x][y][z] = 0;
                    continue;
                }

                mBlocks[x][y][z] =
                    ((x % 2 == 0) && (y % 2 == 0) && (z % 2 == 0)) ? 1 : 0;
            }
        }
    }
}

Chunk::~Chunk(void)
{

}

uint8_t Chunk::getNumNeighbors(void)
{
    return mNeighbors.count;
}

bool Chunk::hasNeighbor(ChunkDirectionEnum dir)
{
    Chunk *neighbor = nullptr;

    switch (dir)
    {
        case pX: neighbor = mNeighbors.posX; break;
        case nX: neighbor = mNeighbors.negX; break;
        case pY: neighbor = mNeighbors.posY; break;
        case nY: neighbor = mNeighbors.negY; break;
        case pZ: neighbor = mNeighbors.pozZ; break;
        case nZ: neighbor = mNeighbors.negZ; break;
    }

    return (neighbor != nullptr) ? true : false;
}

Chunk *Chunk::getNeighbor(ChunkDirectionEnum dir)
{
    switch (dir)
    {
        case pX: return mNeighbors.posX;
        case nX: return mNeighbors.negX;
        case pY: return mNeighbors.posY;
        case nY: return mNeighbors.negY;
        case pZ: return mNeighbors.pozZ;
        case nZ: return mNeighbors.negZ;
    }
}

void Chunk::setNeighbor(ChunkDirectionEnum dir, Chunk *n)
{
    switch (dir)
    {
        case pX: mNeighbors.posX = n; break;
        case nX: mNeighbors.negX = n; break;
        case pY: mNeighbors.posY = n; break;
        case nY: mNeighbors.negY = n; break;
        case pZ: mNeighbors.pozZ = n; break;
        case nZ: mNeighbors.negZ = n; break;
    }

    // Update the number of neighbors.
    if (n == nullptr)
    {
        mNeighbors.count--;
    }
    else
    {
        mNeighbors.count++;
    }
}

glm::ivec3 Chunk::chunkCenterToWorldCoords(glm::ivec3 coords)
{
    return (coords * CHUNK_SIZE) + glm::ivec3(CHUNK_SIZE / 2);
}

void Chunk::initialize(void)
{
    mChunkMesher.allocateBuffers();
}

void Chunk::update(void)
{
    if (!mUpdateRequired)
    {
        return;
    }
    mUpdateRequired = false;

    mChunkMesher.generate(mBlocks, CHUNK_SIZE);

}

void Chunk::render(void)
{
    mChunkMesher.render();
}
