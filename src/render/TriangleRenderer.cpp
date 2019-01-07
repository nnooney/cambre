////////////////////////////////////////////////////////////////////////////////
/// @file TriangleRenderer.cpp
/// @brief A RenderInterface implementation to draw a triangle.
///
/// This file contains the basic Triangle Rendering example from OpenGL.
////////////////////////////////////////////////////////////////////////////////

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "TriangleRenderer.hpp"

TriangleRenderer::TriangleRenderer(void)
{
    mVbo = 0;
    mVao = 0;
}

void TriangleRenderer::initialize(void)
{
    GLfloat vertices[] = {
        -0.8, -0.8,  0.0,
         0.8, -0.8,  0.0,
         0.0,  0.8,  0.0
    };

    glGenVertexArrays(1, &mVao);
    glBindVertexArray(mVao);

    glGenBuffers(1, &mVbo);
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void TriangleRenderer::render(void)
{
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
}
