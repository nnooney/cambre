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

#include "InputManager.hpp"

class Camera
{
public:
    /// @brief The default constructor.
    ///
    /// Constructs a camera instance.
    Camera(void);

    /// @brief Sets the position of the camera.
    ///
    /// This function sets the position of the Camera to the new position.
    void setPosition(glm::vec3 aPosition);

    /// @brief Gets the position of the camera.
    ///
    /// This function gets the position of the Camera.
    glm::vec3 getPosition(void);

    /// @brief Sets the direction of the camera.
    ///
    /// This function sets the direction the Camera is facing.
    void setFacing(glm::vec3 aFacing);

    /// @brief Gets the direction of the camera.
    ///
    /// This function gets the direction the Camera is facing.
    glm::vec3 getFacing(void);

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

    void printData(void);
};

#endif
