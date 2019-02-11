////////////////////////////////////////////////////////////////////////////////
/// @file Chunk.hpp
/// @brief A Class to store several blocks.
///
/// This file contains the Chunk class. It contains several blocks, and it is
/// responsible for rendering all the blocks via one call.
////////////////////////////////////////////////////////////////////////////////

#ifndef _NOONCRAFT_CHUNK_H_
#define _NOONCRAFT_CHUNK_H_

#include <cstdint>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "RenderInterface.hpp"

class Chunk : public RenderInterface
{
public:
    Chunk(void);
    ~Chunk(void);
    void update(void);
    void initialize(void);
    void render(void);
private:
    static const int CHUNK_SIZE = 16;
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
