////////////////////////////////////////////////////////////////////////////////
/// @file Application.hpp
/// @brief The application context manager.
///
/// This file contains the application context manager. It is responsible for
/// maintaining the OpenGL context as well as the GLFW window. Furthermore, it
/// begins the application main loop.
////////////////////////////////////////////////////////////////////////////////

#ifndef _CAMBRE_APPLICATION_H_
#define _CAMBRE_APPLICATION_H_

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "RenderInterface.hpp"
#include "UpdateInterface.hpp"
#include "DynamicObjectInterface.hpp"
#include "InputManager.hpp"

/// @class Application
/// @brief The application context manager.
///
/// The application context manager is responsible for initializing OpenGL and
/// related libraries, maintining the OpenGL context, and managing the GLFW
/// window.
class Application
{
public:
    /// @brief The default constructor.
    ///
    /// This throws an ApplicationException if any of the initialization fails.
    Application(void);

    /// @brief The default destructor.
    ///
    /// The destructor handles the termination of the GLFW window and library.
    ~Application(void);

    /// @brief Run the Application Loop.
    ///
    /// The main application loop listens for input events and renders the
    /// scene.
    void run(void);

    /// @brief Add a RenderInterface to be rendered by the Application.
    ///
    /// This function adds a RenderInterface to the Application so that it will
    /// be rendered when the run method is called.
    void addRenderer(RenderInterface *renderer);

    /// @brief Add an UpdateInterface to be updated by the Application.
    ///
    /// This function adds an UpdateInterface to the Application so that it will
    /// be updated when the run method is called.
    void addUpdater(UpdateInterface *updater);

    /// @brief Add a DynamicObjectInterface to the Application.
    ///
    /// This funciton adds a DynamicObjectInterface to the Application. It will
    /// attach to both the render and update loops.
    void addDynamicObject(DynamicObjectInterface *object);

    /// @brief Attaches an Input Manager to the Application's window.
    ///
    /// This function will register an input manager's low-level functions with
    /// the application's window.
    void registerInputs(InputManager &manager);

    /// @brief Prints the version info for the application.
    ///
    /// This function prints the version of GLFW and OpenGL used by the
    /// application.
    void printVersionInfo(void);

private:
    /// @brief The GLFW Window instance.
    GLFWwindow *mpWindow;

    /// @brief The RenderInterfaces that this application will render.
    std::vector<RenderInterface *> mRenderInterfaces;

    /// @brief The UpdateInterfaces that this application will update.
    std::vector<UpdateInterface *> mUpdateInterfaces;

    /// @brief The InputManager to handle user input.
    ///
    /// Note that the InputManager is static in order to use it for the
    /// callbacks that the GLFW library provides. A side effect means that there
    /// can only be one InputManager.
    static InputManager mInputManager;

    /// @brief The Application's Initialization routine.
    ///
    /// This function gets called prior to entering the main loop. It will
    /// perform the initialization of all resources that have registered with
    /// the application.
    void initialize(void);

    /// @brief The Global Update Loop.
    ///
    /// This function is the entrypoint for running the game logic one step. It
    /// is a part of the application loop.
    void update(void);

    /// @brief The Global Render Loop.
    ///
    /// This function is the entrypoint for rendering the current game state. It
    /// is a part of the application loop.
    void render(void);

    /// @brief The Application's Wrapup routine.
    ///
    /// This function gets called after exiting the main loop. It will wrapup
    /// any resources that were used in the main loop.
    void wrapup(void);

    /// @brief The low-level key callback.
    ///
    /// This function receives GLFW Key Events and forwards them to the
    /// attached InputManager.
    static void KeyCallback(GLFWwindow *window, int key, int scancode,
        int action, int modifiers);

    /// @brief The low-level mouse callback.
    ///
    /// This function receives GLFW Mouse Events and forwards them to the
    /// attached InputManager.
    static void MouseCallback(GLFWwindow *window, double xpos, double ypos);
};

#endif
