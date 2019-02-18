////////////////////////////////////////////////////////////////////////////////
/// @file InputManager.cpp
/// @brief A class that converts input events into game inputs.
///
/// This class manages the low level input events and maps them to game events.
/// It also manages the mapping of keys to game controls. It functions by
/// emitting an event when a key is pressed and when a key is released. These
/// are the eventStart and eventEnd events. Other logic may be used to release
/// a series of events.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Event.hpp"
#include "InputManager.hpp"

InputManager::InputManager(void)
{
    // Resize the subscribers list to the maximum ApplicationEvent.
    mSubscribers.resize(AE_MAX_EVENT_ENUM);

    // Resize the keymap to the maximum GLFW Key Input.
    mKeyEventMap.resize(GLFW_KEY_LAST);

    // Set some default keys (TODO: Remove).
    mKeyEventMap[GLFW_KEY_W] = AE_MOVE_FORWARD;
    mKeyEventMap[GLFW_KEY_S] = AE_MOVE_BACKWARD;
    mKeyEventMap[GLFW_KEY_A] = AE_MOVE_LEFT;
    mKeyEventMap[GLFW_KEY_D] = AE_MOVE_RIGHT;
    mKeyEventMap[GLFW_KEY_SPACE] = AE_MOVE_UP;
    mKeyEventMap[GLFW_KEY_LEFT_SHIFT] = AE_MOVE_DOWN;
}

void InputManager::RegisterInput(
    ApplicationEventEnum code, EventObserver *observer)
{
    mSubscribers[code].push_back(observer);
}

void InputManager::KeyCallback(GLFWwindow *window, int key, int scancode,
    int action, int modifiers)
{
    ApplicationEventStruct event;

    // The code is stored in the keymap.
    event.code = mKeyEventMap[key];

    // The type depends upon the action.
    switch (action)
    {
        case GLFW_PRESS:
            event.type = AE_BEGIN;
            break;
        case GLFW_REPEAT:
            event.type = AE_REPEAT;
            break;
        case GLFW_RELEASE:
            event.type = AE_END;
            break;
    }

    EmitEvent(event);
}

void InputManager::MouseCallback(GLFWwindow *window, double xpos, double ypos)
{
    ApplicationEventStruct event;

    event.code = AE_LOOK_AROUND;
    event.type = AE_SINGLE;

    event.data.axis.x = xpos;
    event.data.axis.y = ypos;

    EmitEvent(event);
}

void InputManager::EmitEvent(ApplicationEventStruct event)
{
    for (EventObserver *observer : mSubscribers[event.code])
    {
        observer->onEvent(event);
    }
}
