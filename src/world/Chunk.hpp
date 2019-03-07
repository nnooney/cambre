////////////////////////////////////////////////////////////////////////////////
/// @file Chunk.hpp
/// @brief A Class to store several blocks.
///
/// This file contains the Chunk class. It contains several blocks, and it is
/// responsible for rendering all the blocks via one call.
////////////////////////////////////////////////////////////////////////////////

#ifndef _CAMBRE_CHUNK_H_
#define _CAMBRE_CHUNK_H_

#include <cstdint>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "DynamicObjectInterface.hpp"

/// @class Chunk
/// @brief A class to store several blocks.
///
/// This class groups related blocks into a single unit for the GPU to render.
/// The number of blocks is determined by the static variable CHUNK_SIZE.
class Chunk : public DynamicObjectInterface
{
public:
    Chunk(void);
    Chunk(int x, int y, int z);
    virtual ~Chunk(void);
    void initialize(void);
    void update(void);
    void render(void);

    static const int CHUNK_SIZE = 16;

private:
    /// @brief The coordinates of this chunk in the world.
    int mx;
    int my;
    int mz;

    /// @brief The array of blocks belonging to this chunk.
    uint8_t mBlocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];

    /// @brief The OpenGL Vertex Array Object
    GLuint mVao;

    /// @brief The OpenGL Vertex Buffer Object
    GLuint mVbo;

    /// @brief The Mesh Data for the VBO.
    glm::tvec4<GLbyte> mMeshData[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE * 36];
    int mMeshElements;

    /// @brief A flag indicating updates need to occur.
    bool mUpdateRequired;
};

#endif
