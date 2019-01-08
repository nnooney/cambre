////////////////////////////////////////////////////////////////////////////////
/// @file Camera.cpp
/// @brief A class that provides an interface for the camera.
///
/// This class supplies the view and projection matrices to the Application so
/// that the user can move around.
////////////////////////////////////////////////////////////////////////////////

#include <glm/gtc/matrix_transform.hpp>

#include "Camera.hpp"

Camera::Camera(void)
{
    mPosition = glm::vec3(0.0, 0.0, -4.0);
    mYaw = 90;
    mPitch = 0;
    mFacing = glm::normalize(glm::vec3(
        glm::cos(glm::radians(mPitch)) * glm::cos(glm::radians(mYaw)),
        glm::sin(glm::radians(mPitch)),
        glm::cos(glm::radians(mPitch)) * glm::sin(glm::radians(mYaw))
    ));
}

void Camera::updatePosition(glm::vec3 deltaPosition)
{
    mPosition += deltaPosition;
}

void Camera::updateDirection(glm::vec2 deltaDirection)
{
    mYaw += deltaDirection.x;
    mPitch += deltaDirection.y;

    mFacing = glm::normalize(glm::vec3(
        glm::cos(glm::radians(mPitch)) * glm::cos(glm::radians(mYaw)),
        glm::sin(glm::radians(mPitch)),
        glm::cos(glm::radians(mPitch)) * glm::sin(glm::radians(mYaw))
    ));
}

glm::mat4 Camera::getView(void)
{
    return glm::lookAt(
        mPosition,
        mPosition + mFacing,
        glm::vec3(0.0, 1.0, 0.0));
}
