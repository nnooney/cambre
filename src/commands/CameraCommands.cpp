////////////////////////////////////////////////////////////////////////////////
/// @file CameraCommands.cpp
/// @brief Command implementations for the Camera.
///
/// This file contains several command classes that the Camera responds to. Most
/// of these commands are generated and responded to by the InputManager.
////////////////////////////////////////////////////////////////////////////////

#include "CameraCommands.hpp"


LookCommand::LookCommand(Camera *camera, float yaw, float pitch)
{
    mCamera = camera;
    mYaw = yaw;
    mPitch = pitch;
}

void LookCommand::execute(void)
{
    mCamera->setYaw(mYaw);
    mCamera->setPitch(mPitch);
}


MoveCommand::MoveCommand(Camera *camera, glm::vec3 position)
{
    mCamera = camera;
    mPosition = position;
}

void MoveCommand::execute(void)
{
    mCamera->setPosition(mPosition);
}
