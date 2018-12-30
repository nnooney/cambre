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

#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

    /// @brief Prints the version info for the application.
    ///
    /// This function prints the version of GLFW and OpenGL used by the
    /// application.
    void printVersionInfo(void);

private:
    /// The GLFW Window instance
    GLFWwindow *mpWindow;
};

#endif
