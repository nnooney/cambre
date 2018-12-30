////////////////////////////////////////////////////////////////////////////////
/// @file Application.cpp
/// @brief The application context manager.
///
/// This file contains the application context manager. It is responsible for
/// maintaining the OpenGL context as well as the GLFW window. Furthermore, it
/// begins the application main loop.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "ApplicationException.hpp"
#include "Application.hpp"


Application::Application(void)
{
    // Initialize GLFW
    if (!glfwInit())
    {
        throw ApplicationException("GLFW Initialization Failure");
    }

    // Construct the Window
    mpWindow = glfwCreateWindow(640, 480, "Nooncraft", NULL, NULL);
    if (!mpWindow)
    {
        throw ApplicationException("GLFW Window Creation Failure");
    }

    // Make the window's context current
    glfwMakeContextCurrent(mpWindow);

    // Initialize GLEW
    if (GLEW_OK != glewInit())
    {
        throw ApplicationException("GLEW Initialization Failure");
    }
}

Application::~Application(void)
{
    // Destruct the window
    glfwDestroyWindow(mpWindow);

    // Terminate GLFW
    glfwTerminate();
}

void Application::run(void)
{
    // The main loop
    while (!glfwWindowShouldClose(mpWindow))
    {
        glfwSwapBuffers(mpWindow);
        glfwPollEvents();
    }
}

void Application::printVersionInfo(void)
{
    int major, minor, revision;

    glfwGetVersion(&major, &minor, &revision);
    std::cout << "GLFW Version "
        << major << "." << minor << "." << revision << std::endl;

    std::cout << "OpenGL Version " << glGetString(GL_VERSION) << std::endl;
}
