////////////////////////////////////////////////////////////////////////////////
/// @file Region.hpp
/// @brief A class to handle multiple chunks.
///
/// This file contains the Region class. Multiple chunks get organized into a
/// region. The region is responsible for maintaining the list of chunks as well
/// as loading and unloading the chunks.
////////////////////////////////////////////////////////////////////////////////

#ifndef _CAMBRE_REGION_H_
#define _CAMBRE_REGION_H_

#include <unordered_map>

#include <glm/glm.hpp>

#include "CameraController.hpp"
#include "Chunk.hpp"
#include "DynamicObjectInterface.hpp"
#include "InputManager.hpp"
#include "ShaderProgram.hpp"
#include "Specialization.hpp"

/// @class Region
/// @brief A class to handle multiple chunks.
///
/// A Region is a logical grouping of chunks. The chunks belonging to a region
/// can be updated over time. One of the primary regions is the region around
/// the player.
class Region : public DynamicObjectInterface
{
public:
    Region(void);
    ~Region(void);
    void initialize(void);
    void update(void);
    void render(void);

    /// @brief Use the ShaderProgram for rendering.
    ///
    /// This call sets the shader for use when rendering the region.
    void useShader(ShaderProgram &shader);

    /// @brief Use the CameraController for rendering.
    ///
    /// This call sets the camera controller for use when rendering the region.
    void useCameraController(CameraController &cc);

    /// @brief Register to listen for inputs.
    ///
    /// This function attaches the region to an input manager so it can be
    /// updated via user input.
    void registerWith(InputManager &manager);

private:
    /// @brief The set of chunks managed by the Region.
    std::unordered_map<glm::ivec3, Chunk*> mChunks;

    /// @brief The Shader Program used by this application.
    ShaderProgram mShaderProgram;
    GLuint mUniformVP;
    GLuint mUniformModel;

    /// @brief The Camera Controller that gives life to the camera.
    CameraController mCameraController;
};

#endif
