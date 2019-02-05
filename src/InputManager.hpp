////////////////////////////////////////////////////////////////////////////////
/// @file InputManager.hpp
/// @brief A class that converts input events into game inputs.
///
/// This class manages the low level input events and maps them to game events.
/// It also manages the mapping of keys to game controls. It functions by
/// emitting an event when a key is pressed and when a key is released. These
/// are the eventStart and eventEnd events. Other logic may be used to release
/// a series of events.
////////////////////////////////////////////////////////////////////////////////

#ifndef _NOONCRAFT_INPUT_MANAGER_H_
#define _NOONCRAFT_INPUT_MANAGER_H_

#include <list>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Event.hpp"
#include "EventObserver.hpp"

class InputManager
{
public:
    /// @brief The default constructor.
    ///
    /// Constructs an input manager instance.
    InputManager(void);

    /// @brief Attaches a callback to an event code.
    ///
    /// This function is used to register event callbacks with the InputManager.
    void RegisterInput(ApplicationEventEnum code, EventObserver *observer);

    /// @brief The low-level key callback.
    ///
    /// This function processes GLFW Key Events and converts them to application
    /// events.
    void KeyCallback(GLFWwindow *window, int key, int scancode,
        int action, int modifiers);

    /// @brief The low-level mouse callback.
    ///
    /// This function processes GLFW Mouse Events and converts them to
    /// application events.
    void MouseCallback(GLFWwindow *window, double xpos, double ypos);

    /// @brief A function to emit an event to all registered observers.
    ///
    /// This function sends an event to all registered EventObservers.
    void EmitEvent(ApplicationEventStruct event);

private:

    /// @brief The list of subscribers registered to each event.
    ///
    /// Each index in the vector corresponds to a single ApplicationEventEnum.
    /// The vector stores a list of callbacks that will be called when the
    /// corresponding event occurs. Every callback has the form:
    ///    void callback(ApplicationEvent e);
    std::vector<std::list<EventObserver *>> mSubscribers;

    /// @brief The map of keys to events.
    std::vector<ApplicationEventEnum> mKeyEventMap;
};

#endif
