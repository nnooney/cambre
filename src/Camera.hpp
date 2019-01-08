////////////////////////////////////////////////////////////////////////////////
/// @file Camera.hpp
/// @brief A class that provides an interface for the camera.
///
/// This class supplies the view and projection matrices to the Application so
/// that the user can move around.
////////////////////////////////////////////////////////////////////////////////

#ifndef _NOONCRAFT_CAMERA_H_
#define _NOONCRAFT_CAMERA_H_

#include <glm/glm.hpp>

class Camera
{
public:
    /// @brief The default constructor.
    ///
    /// Constructs a camera instance.
    Camera(void);

    /// @brief Updates the position of the camera.
    ///
    /// This function updates the position of the camera by using the vector and
    /// combining it with the camera's current position.
    void updatePosition(glm::vec3 deltaPosition);

    /// @brief Updates the direction the camera is facing.
    ///
    /// This function updates the direction the camera is facing. The vector
    /// provided contains the delta yaw and delta pitch.
    void updateDirection(glm::vec2 deltaDirection);

    /// @brief Retrieves the View matrix for rendering.
    ///
    /// This function returns the view matrix represented by the camera's
    /// position, direction, and up vector.
    glm::mat4 getView(void);

private:
    /// @brief The position of the camera in the world.
    glm::vec3 mPosition;

    /// @brief The direction the camera is facing.
    glm::vec3 mFacing;

    /// @brief The yaw of the camera.
    float mYaw;

    /// @brief The pitch of the camera.
    float mPitch;
};

#endif
