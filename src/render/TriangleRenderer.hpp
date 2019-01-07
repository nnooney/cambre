////////////////////////////////////////////////////////////////////////////////
/// @file TriangleRenderer.hpp
/// @brief A RenderInterface implementation to draw a triangle.
///
/// This file contains the basic Triangle Rendering example from OpenGL.
////////////////////////////////////////////////////////////////////////////////

#ifndef _NOONCRAFT_TRIANGLE_RENDERER_H_
#define _NOONCRAFT_TRIANGLE_RENDERER_H_

#include "RenderInterface.hpp"

class TriangleRenderer : public RenderInterface
{
public:
    /// @brief The default constructor.
    ///
    /// Construct and allocate the buffers needed for this object.
    TriangleRenderer(void);

    /// @brief The initialize function.
    ///
    /// This function implements the initialize interface from the
    /// RenderInterface. It attaches data and enables the shader program
    /// attributes.
    void initialize(void);

    /// @brief The render function.
    ///
    /// This function draws a colorful triangle.
    void render(void);

private:
    /// @brief The vertex buffer object used to hold the Triangle Data.
    GLuint mVbo;

    /// @brief The vertex array object.
    GLuint mVao;
};

#endif
