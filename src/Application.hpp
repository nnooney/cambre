////////////////////////////////////////////////////////////////////////////////
/// @file Application.hpp
/// @brief The application context manager.
///
/// This file contains the application context manager. It is responsible for
/// maintaining the OpenGL context as well as the GLFW window. Furthermore, it
/// begins the application main loop.
////////////////////////////////////////////////////////////////////////////////

#ifndef _NOONCRAFT_APPLICATION_H_
#define _NOONCRAFT_APPLICATION_H_

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ShaderProgram.hpp"
#include "RenderInterface.hpp"
#include "Camera.hpp"
#include "CameraController.hpp"
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

    /// @brief Use the ShaderProgram for rendering the application.
    ///
    /// This call saves the shader program for rendering via the application.
    void useShader(ShaderProgram shader);

    /// @brief Add a RenderInterface to be rendered by the Application.
    ///
    /// This function adds a RenderInterface to the Application so that it will
    /// be rendered when the run method is calld.
    void addRenderer(RenderInterface *renderer);

    /// @brief Attaches an Input Manager to the Application's window.
    ///
    /// This function will register an input manager's low-level functions with
    /// the application's window.
    void registerInputs(InputManager manager);

    /// @brief Prints the version info for the application.
    ///
    /// This function prints the version of GLFW and OpenGL used by the
    /// application.
    void printVersionInfo(void);

private:
    /// @brief The GLFW Window instance.
    GLFWwindow *mpWindow;

    /// @brief The Shader Program used by this application.
    ShaderProgram mShaderProgram;

    /// @brief The RenderInterfaces that this application will render.
    std::vector<RenderInterface *> mRenderInterfaces;

    /// @brief The Camera used to view the world.
    Camera mCamera;

    /// @brief The Camera Controller that gives life to the camera.
    CameraController mCameraController;

    /// @brief The InputManager to handle user input.
    ///
    /// Note that the InputManager is static in order to use it for the
    /// callbacks that the GLFW library provides. A side effect means that there
    /// can only be one InputManager.
    static InputManager mInputManager;

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
