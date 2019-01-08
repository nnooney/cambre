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

    /// @brief Attach Window Callbacks.
    ///
    /// This function attaches the callbacks necessary to handle GLFW events.
    void attachCallbacks(void);

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
    std::vector<RenderInterface *>mRenderInterfaces;

    /// @brief The Camera used to view the world.
    static Camera mCamera;

    /// @brief The GLFW Key Event Callback.
    ///
    /// This function processes Key Events.
    static void KeyCallback(GLFWwindow *window, int key, int scancode,
        int action, int modifiers);

    /// @brief The GLFW Mouse Event Callback.
    ///
    /// This function processes Mouse Events.
    static void MouseCallback(GLFWwindow *window, double xpos, double ypos);
};

#endif
