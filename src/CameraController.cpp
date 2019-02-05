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
    glm::vec3 position = mpCamera->getPosition();
    glm::vec3 direction = mpCamera->getFacing();

    Command *cmd;

    switch(event.code)
    {
        case AE_LOOK_AROUND:
            // Calculate the new direction.
            direction.x += glm::cos(glm::radians(event.data.axis.y)) *
                glm::cos(glm::radians(event.data.axis.x));
            direction.y -= glm::sin(glm::radians(event.data.axis.y));
            direction.z += glm::cos(glm::radians(event.data.axis.y)) *
                glm::sin(glm::radians(event.data.axis.x));

            // Create the command.
            cmd = new LookCommand(mpCamera, direction);
            break;

        case AE_MOVE_BACKWARD:
            // Calculate the new position.
            position -= direction;

            cmd = new MoveCommand(mpCamera, position);
            break;

        case AE_MOVE_FORWARD:
            // Calculate the new position.
            position += direction;

            cmd = new MoveCommand(mpCamera, position);
            break;

        case AE_MOVE_LEFT:
            // Calculate the new position.
            position += glm::normalize(glm::cross(
                position + direction,
                glm::vec3(0.0, 1.0, 0.0)));

            cmd = new MoveCommand(mpCamera, position);
            break;

        case AE_MOVE_RIGHT:
            // Calculate the new position.
            position -= glm::normalize(glm::cross(
                position + direction,
                glm::vec3(0.0, 1.0, 0.0)));

            cmd = new MoveCommand(mpCamera, position);
            break;

        default:
            break;
    }

    cmd->execute();
    delete cmd;
}
