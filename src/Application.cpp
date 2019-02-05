////////////////////////////////////////////////////////////////////////////////
/// @file Application.cpp
/// @brief The application context manager.
///
/// This file contains the application context manager. It is responsible for
/// maintaining the OpenGL context as well as the GLFW window. Furthermore, it
/// begins the application main loop.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ApplicationException.hpp"
#include "Application.hpp"

InputManager Application::mInputManager;

static void ErrorCallback(int error, const char *msg)
{
    std::cerr << "GLFW Error " << error << ": " << msg << std::endl;
}

Application::Application(void) : mCameraController(&mCamera)
{
    // Initialize GLFW
    if (!glfwInit())
    {
        throw ApplicationException("GLFW Initialization Failure");
    }

    // Set the error callback
    glfwSetErrorCallback(ErrorCallback);

    // Construct the Window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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

void Application::registerInputs(InputManager manager)
{
    mInputManager = manager;
    mCameraController.registerWith(&mInputManager);

    glfwSetKeyCallback(mpWindow, KeyCallback);
    glfwSetInputMode(mpWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(mpWindow, MouseCallback);
}

void Application::run(void)
{
    GLuint uMVP;

    // Configure OpenGL
    glEnable(GL_DEPTH_TEST);

    uMVP = glGetUniformLocation(mShaderProgram.getProgram(), "MVP");

    // Perform RenderInterface Initialization
    for (RenderInterface *renderer : mRenderInterfaces)
    {
        renderer->initialize();
    }

    // The main loop
    std::cout << "Beginning Main Loop ..." << std::endl;
    while (!glfwWindowShouldClose(mpWindow))
    {
        GLint width, height;

        glfwGetFramebufferSize(mpWindow, &width, &height);
        GLfloat aspectRatio = (float)width/height;
        glViewport(0, 0, width, height);
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(mShaderProgram.getProgram());

        glm::mat4 view = mCamera.getView();
        glm::mat4 proj = glm::perspective(
            glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
        glUniformMatrix4fv(uMVP, 1, GL_FALSE, glm::value_ptr(proj * view));

        // Perform RenderInterface Rendering
        for (RenderInterface *renderer : mRenderInterfaces)
        {
            renderer->render();
        }

        glfwSwapBuffers(mpWindow);
        glfwPollEvents();
    }
    std::cout << "Exiting Main Loop ..." << std::endl;

    // Perform RenderInterface Wrapup
    for (RenderInterface *renderer : mRenderInterfaces)
    {
        renderer->wrapup();
    }
}

void Application::useShader(ShaderProgram shader)
{
    // Ensure that the shader is ready to be used.
    if (shader.isReadyToUse() != true)
    {
        std::cerr << "Application Shader is not ready to use" << std::endl;
        return;
    }

    // Save the shader reference being used.
    mShaderProgram = shader;

    // Indicate that the program is being used for OpenGL.
    mShaderProgram.activate();
}

void Application::addRenderer(RenderInterface *renderer)
{
    mRenderInterfaces.push_back(renderer);
}

void Application::printVersionInfo(void)
{
    int major, minor, revision;

    glfwGetVersion(&major, &minor, &revision);
    std::cout << "GLFW Version "
        << major << "." << minor << "." << revision << std::endl;

    std::cout << "OpenGL Version " << glGetString(GL_VERSION) << std::endl;
}

void Application::KeyCallback(GLFWwindow *window, int key, int scancode,
    int action, int modifiers)
{
    mInputManager.KeyCallback(window, key, scancode, action, modifiers);
}

void Application::MouseCallback(GLFWwindow *window, double xpos, double ypos)
{

    mInputManager.MouseCallback(window, xpos, ypos);
}
