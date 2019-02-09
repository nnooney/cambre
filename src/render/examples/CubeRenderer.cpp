////////////////////////////////////////////////////////////////////////////////
/// @file CubeRenderer.cpp
/// @brief A class to render a single cube.
///
/// This class renders a cube, the basic building block of voxels.
////////////////////////////////////////////////////////////////////////////////

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "CubeRenderer.hpp"

constexpr GLfloat CubeRenderer::mColorData[];
constexpr GLfloat CubeRenderer::mVertexData[];
constexpr GLushort CubeRenderer::mIndexData[];

CubeRenderer::CubeRenderer(void)
{
    mVao = 0;
    mVertexVbo = 0;
    mColorVbo = 0;
    mIbo = 0;
}

void CubeRenderer::initialize(void)
{
    glGenVertexArrays(1, &mVao);
    glBindVertexArray(mVao);

    glGenBuffers(1, &mVertexVbo);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexVbo);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(mVertexData),
        mVertexData,
        GL_STATIC_DRAW);

    glGenBuffers(1, &mColorVbo);
    glBindBuffer(GL_ARRAY_BUFFER, mColorVbo);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(mColorData),
        mColorData,
        GL_STATIC_DRAW);

    glGenBuffers(1, &mIbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIbo);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(mIndexData),
        mIndexData,
        GL_STATIC_DRAW);
}

void CubeRenderer::render(void)
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, mVertexVbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, mColorVbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIbo);

    glDrawElements(
        GL_TRIANGLES,
        sizeof(mIndexData)/sizeof(GLushort),
        GL_UNSIGNED_SHORT,
        0);

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
}
