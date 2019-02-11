////////////////////////////////////////////////////////////////////////////////
/// @file Camera.cpp
/// @brief A class that provides an interface for the camera.
///
/// This class supplies the view and projection matrices to the Application so
/// that the user can move around.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

#include "Camera.hpp"

Camera::Camera(void)
{
    mPosition = glm::vec3(0.0, 0.0, -10.0);
    mYaw = 90.0;
    mPitch = 0.0;
    updateFacing();
}

void Camera::setPosition(glm::vec3 aPosition)
{
    mPosition = aPosition;
}

glm::vec3 Camera::getPosition(void)
{
    return mPosition;
}

glm::vec3 Camera::getFacing(void)
{
    return mFacing;
}

void Camera::setYaw(float aYaw)
{
    mYaw = aYaw;
    updateFacing();
}

float Camera::getYaw(void)
{
    return mYaw;
}

void Camera::setPitch(float aPitch)
{
    mPitch = aPitch;
    updateFacing();
}

float Camera::getPitch(void)
{
    return mPitch;
}

glm::mat4 Camera::getView(void)
{
    return glm::lookAt(
        mPosition,
        mPosition + mFacing,
        glm::vec3(0.0, 1.0, 0.0));
}

void Camera::updateFacing(void)
{
    mFacing.x = glm::cos(glm::radians(mYaw)) * glm::cos(glm::radians(mPitch));
    mFacing.y = glm::sin(glm::radians(mPitch));
    mFacing.z = glm::sin(glm::radians(mYaw)) * glm::cos(glm::radians(mPitch));
    if (mFacing.x != 0 && mFacing.y != 0 && mFacing.z != 0)
    {
        mFacing = glm::normalize(mFacing);
    }
}

void Camera::printData(void)
{
    std::cout << "Pos: (" << mPosition.x << ", " << mPosition.y << ", " <<
        mPosition.z << ") Dir: (" << mFacing.x << ", " << mFacing.y << ", " <<
        mFacing.z << ") Yaw: " << mYaw << " Pitch: " << mPitch << std::endl;
}
