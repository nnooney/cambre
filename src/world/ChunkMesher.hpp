////////////////////////////////////////////////////////////////////////////////
/// @file ChunkMesher.hpp
/// @brief A mesher for the chunk class.
///
/// This file implements the Mesh Interface provided for the Chunk Class.
////////////////////////////////////////////////////////////////////////////////

#ifndef _CAMBRE_CHUNK_MESHER_H_
#define _CAMBRE_CHUNK_MESHER_H_

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "MeshInterface.hpp"

class ChunkMesher : public MeshInterface
{
public:
    ChunkMesher(void);
    ChunkMesher(unsigned int meshSize);
    ~ChunkMesher(void);

    void allocateBuffers(void);
    void generate(uint8_t aData[16][16][16], int size);
    void render(void);
private:
    /// @brief The OpenGL Vertex Array Object
    GLuint mVao;

    /// @brief The OpenGL Vertex Buffer Object
    GLuint mVbo;

    /// @brief The Mesh Data for the VBO.
    std::vector<GLbyte> mMeshData;

    /// @brief Adds a triangle to the mesh.
    ///
    /// This function adds a triangle to the mesh.
    void addTriangleToMesh(int x, int y, int z, int type);
};

#endif
