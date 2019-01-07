////////////////////////////////////////////////////////////////////////////////
/// @file CubeRenderer.hpp
/// @brief A class to render a single cube.
///
/// This class renders a cube, the basic building block of voxels.
////////////////////////////////////////////////////////////////////////////////

#ifndef _NOONCRAFT_CUBE_RENDERER_H_
#define _NOONCRAFT_CUBE_RENDERER_H_

#include "RenderInterface.hpp"

class CubeRenderer : public RenderInterface
{
public:
    /// @brief The default constructor.
    ///
    /// Construct the data needed to render a cube.
    CubeRenderer(void);

    /// @brief The initialize function.
    ///
    /// This function implements the initialize interface from the
    /// RenderInterface. It attaches data and enables the shader program
    /// attributes.
    void initialize(void);

    /// @brief The render function.
    ///
    /// This function is responsible for the OpenGL draw calls.
    void render(void);

private:
    /// @brief The OpenGL Vertex Array Object
    GLuint mVao;

    /// @brief The OpenGL Vertex Array Buffers
    GLuint mVertexVbo;
    GLuint mColorVbo;

    /// @brief The OpenGL Index Buffer Object
    GLuint mIbo;

    /// @brief The Model View Projection Uniform in the Shader.
    GLint mMVP;

    /// @brief The Vertices of the Cube.
    static constexpr GLfloat mVertexData[] = {
        // Front
        -1.0, -1.0,  1.0,
         1.0, -1.0,  1.0,
         1.0,  1.0,  1.0,
        -1.0,  1.0,  1.0,
        // Back
        -1.0, -1.0, -1.0,
         1.0, -1.0, -1.0,
         1.0,  1.0, -1.0,
        -1.0,  1.0, -1.0
    };

    /// @brief The Color Data for the Cube.
    static constexpr GLfloat mColorData[] = {
        // Front colors
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0,
        1.0, 1.0, 1.0,
        // Back colors
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0,
        1.0, 1.0, 1.0
    };

    /// @brief The Index Data for the Cube.
    static constexpr GLushort mIndexData[] = {
        // Front
        0, 1, 2,
        2, 3, 0,
        // Right
        1, 5, 6,
        6, 2, 1,
        // Back
        7, 6, 5,
        5, 4, 7,
        // Left
        4, 0, 3,
        3, 7, 4,
        // Bottom
        4, 5, 1,
        1, 0, 4,
        // Top
        3, 2, 6,
        6, 7, 3
    };
};

#endif
