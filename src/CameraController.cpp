////////////////////////////////////////////////////////////////////////////////
/// @file CameraController.cpp
/// @brief A class that generates camera commands from events.
///
/// This class listens for applicable camera events and generates a stream of
/// commands that it forwards onto a Camera instance.
////////////////////////////////////////////////////////////////////////////////

#include "CameraCommands.hpp"
#include "InputManager.hpp"

#include "CameraController.hpp"

CameraController::CameraController(Camera *camera)
{
    mpCamera = camera;

    mEventStates.resize(AE_MAX_EVENT_ENUM);
}

void CameraController::registerWith(InputManager *manager)
{
    manager->RegisterInput(AE_MOVE_FORWARD, this);
    manager->RegisterInput(AE_MOVE_BACKWARD, this);
    manager->RegisterInput(AE_MOVE_LEFT, this);
    manager->RegisterInput(AE_MOVE_RIGHT, this);
    manager->RegisterInput(AE_LOOK_AROUND, this);
}

void CameraController::onEvent(ApplicationEventStruct event)
{
    mEventStates[event.code] = event.type;

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

void CameraController::updatePosition(void)
{
    glm::vec3 position = mpCamera->getPosition();
    glm::vec3 direction = mpCamera->getFacing();
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
                glm::vec3(0.0, 1.0, 0.0)));
    }
    if (mEventStates[AE_MOVE_RIGHT] == AE_BEGIN)
    {
        deltaPos += glm::normalize(glm::cross(
                direction,
                glm::vec3(0.0, 1.0, 0.0)));
    }

    // deltaPos contains the new location to move to. In order to control the
    // movement speed, normalize the difference between the current and new
    // position.
    if (deltaPos != glm::vec3(0))
    {
        deltaPos = glm::normalize(deltaPos);
    }

    // Create the command.
    cmd = new MoveCommand(mpCamera, position + deltaPos);
    cmd->execute();
    delete cmd;
}

void CameraController::updateFacing(void)
{
    float yaw = mpCamera->getYaw();
    float pitch = mpCamera->getPitch();

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
        yaw += dx;
        pitch += dy;

        // Create the command.
        cmd = new LookCommand(mpCamera, yaw, pitch);
        cmd->execute();
        delete cmd;
    }
}
