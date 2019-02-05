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
    mPosition = glm::vec3(0.0, 0.0, -4.0);
    mFacing = glm::vec3(0.0, 0.0, 1.0);
}

void Camera::setPosition(glm::vec3 aPosition)
{
    mPosition = aPosition;
    printData();
}

glm::vec3 Camera::getPosition(void)
{
    return mPosition;
}


void Camera::setFacing(glm::vec3 aFacing)
{
    mFacing = glm::normalize(aFacing);
    printData();
}


glm::vec3 Camera::getFacing(void)
{
    return mFacing;
}

glm::mat4 Camera::getView(void)
{
    return glm::lookAt(
        mPosition,
        mPosition + mFacing,
        glm::vec3(0.0, 1.0, 0.0));
}

void Camera::printData(void)
{
    std::cout << "Pos: (" << mPosition.x << ", " << mPosition.y << ", " <<
        mPosition.z << ") Dir: (" << mFacing.x << ", " << mFacing.y << ", " <<
        mFacing.z << ")" << std::endl;
}
