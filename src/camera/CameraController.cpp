////////////////////////////////////////////////////////////////////////////////
/// @file CameraController.cpp
/// @brief A class that generates camera commands from events.
///
/// This class listens for applicable camera events and generates a stream of
/// commands that it forwards onto a Camera instance.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "CameraCommands.hpp"
#include "InputManager.hpp"

#include "CameraController.hpp"

static const glm::vec3 VECTOR_UP = glm::vec3(0.0, 1.0, 0.0);
static const float MOVEMENT_SPEED = 0.5;
static const float LOOK_SPEED = 0.25;

CameraController::CameraController(void)
{
    mEventStates.resize(AE_MAX_EVENT_ENUM);
}

void CameraController::registerWith(InputManager &manager)
{
    manager.RegisterInput(AE_MOVE_FORWARD, this);
    manager.RegisterInput(AE_MOVE_BACKWARD, this);
    manager.RegisterInput(AE_MOVE_LEFT, this);
    manager.RegisterInput(AE_MOVE_RIGHT, this);
    manager.RegisterInput(AE_MOVE_UP, this);
    manager.RegisterInput(AE_MOVE_DOWN, this);
    manager.RegisterInput(AE_LOOK_AROUND, this);
}

void CameraController::onEvent(ApplicationEventStruct event)
{
    if (event.type != AE_REPEAT)
    {
        mEventStates[event.code] = event.type;
    }

    switch(event.code)
    {
        case AE_LOOK_AROUND:
            mCursorData = event.data;
            break;

        default:
            break;
    }
}

void CameraController::update(void)
{
    updatePosition();
    updateFacing();
}

glm::mat4 CameraController::getView(void)
{
    return mCamera.getView();
}

glm::vec3 CameraController::getPosition(void)
{
    return mCamera.getPosition();
}

void CameraController::updatePosition(void)
{
    glm::vec3 position = mCamera.getPosition();
    glm::vec3 direction = mCamera.getFacing();
    glm::vec3 deltaPos = glm::vec3(0);

    Command *cmd;

    // Calculate the new position of the Camera based upon which events have
    // been received.
    if (mEventStates[AE_MOVE_BACKWARD] == AE_BEGIN)
    {
        deltaPos -= direction;
    }
    if (mEventStates[AE_MOVE_FORWARD] == AE_BEGIN)
    {
        deltaPos += direction;
    }
    if (mEventStates[AE_MOVE_LEFT] == AE_BEGIN)
    {
        deltaPos -= glm::normalize(glm::cross(
                direction,
                VECTOR_UP));
    }
    if (mEventStates[AE_MOVE_RIGHT] == AE_BEGIN)
    {
        deltaPos += glm::normalize(glm::cross(
                direction,
                VECTOR_UP));
    }
    if (mEventStates[AE_MOVE_UP] == AE_BEGIN)
    {
        deltaPos += VECTOR_UP;
    }
    if (mEventStates[AE_MOVE_DOWN] == AE_BEGIN)
    {
        deltaPos -= VECTOR_UP;
    }

    // deltaPos contains the new location to move to. In order to control the
    // movement speed, normalize the difference between the current and new
    // position.
    if (deltaPos != glm::vec3(0))
    {
        deltaPos = glm::normalize(deltaPos) * MOVEMENT_SPEED;
    }

    // Create the command.
    cmd = new MoveCommand(&mCamera, position + deltaPos);
    cmd->execute();
    delete cmd;
}

void CameraController::updateFacing(void)
{
    float yaw = mCamera.getYaw();
    float pitch = mCamera.getPitch();

    Command *cmd;

    // Obtain the deltas in cursor position.
    float dx = mCursorData.axis.x - mPrevCursorData.axis.x;
    float dy = mPrevCursorData.axis.y - mCursorData.axis.y;

    // Update the Previous Cursor Position Data.
    mPrevCursorData = mCursorData;

    // Avoid spikes in the direction.
    if (dx > 100 || dy > 100)
    {
        return;
    }

    // If an update occured, move the camera direction.
    if (dx != 0 || dy != 0)
    {
        // Calculate the new direction.
        yaw += dx * LOOK_SPEED;
        pitch += dy * LOOK_SPEED;

        // Create the command.
        cmd = new LookCommand(&mCamera, yaw, pitch);
        cmd->execute();
        delete cmd;
    }
}
