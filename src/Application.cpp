////////////////////////////////////////////////////////////////////////////////
/// @file Application.cpp
/// @brief The application context manager.
///
/// This file contains the application context manager. It is responsible for
/// maintaining the OpenGL context as well as the GLFW window. Furthermore, it
/// begins the application main loop.
////////////////////////////////////////////////////////////////////////////////

#include <chrono>
#include <iostream>
#include <thread>

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

Application::Application(void)
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
    mpWindow = glfwCreateWindow(640, 480, "Cambre", NULL, NULL);
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
    double curTime, updateTime;
    const double delta = 1.0/60.0;

    // Configure OpenGL
    glEnable(GL_DEPTH_TEST);

    mUniformMVP = glGetUniformLocation(mShaderProgram.getProgram(), "MVP");

    // Initialize necessary resources
    initialize();

    // The main loop
    std::cout << "Beginning Main Loop ..." << std::endl;
    updateTime = glfwGetTime();
    while (!glfwWindowShouldClose(mpWindow))
    {
        curTime = glfwGetTime();
        if (curTime >= updateTime)
        {
            updateTime += delta;
            update();
            if (curTime < updateTime)
            {
                render();
            }
        }
        else
        {
            // Try to sleep for the remainder of the frame in order to reduce
            // CPU usage.
            int ms = (updateTime - curTime) * 1000;
            if (ms > 0)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(ms));
            }
        }
    }
    std::cout << "Exiting Main Loop ..." << std::endl;

    // Wrapup necessary resources
    wrapup();
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

void Application::addUpdater(UpdateInterface *updater)
{
    mUpdateInterfaces.push_back(updater);
}

void Application::addDynamicObject(DynamicObjectInterface *object)
{
    addRenderer(object);
    addUpdater(object);
}

void Application::printVersionInfo(void)
{
    int major, minor, revision;

    glfwGetVersion(&major, &minor, &revision);
    std::cout << "GLFW Version "
        << major << "." << minor << "." << revision << std::endl;

    std::cout << "OpenGL Version " << glGetString(GL_VERSION) << std::endl;

    std::cout << "GLM Version " << GLM_VERSION_MAJOR << "." << GLM_VERSION_MINOR
        << "." << GLM_VERSION_PATCH << "." << GLM_VERSION_REVISION << std::endl;
}

void Application::initialize(void)
{
    // Perform RenderInterface Initialization
    for (RenderInterface *renderer : mRenderInterfaces)
    {
        renderer->initialize();
    }

    // Perform UpdateInterface Initialization
    for (UpdateInterface *updater : mUpdateInterfaces)
    {
        updater->initialize();
    }
}

void Application::update(void)
{
    mCameraController.update();

    // Perform UpdateInterface Updating
    for (UpdateInterface *updater : mUpdateInterfaces)
    {
        updater->update();
    }


    glfwPollEvents();
}

void Application::render(void)
{
    GLint width, height;

    glfwGetFramebufferSize(mpWindow, &width, &height);
    GLfloat aspectRatio = (float)width/height;
    glViewport(0, 0, width, height);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(mShaderProgram.getProgram());

    glm::mat4 view = mCameraController.getView();
    glm::mat4 proj = glm::perspective(
        glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
    glUniformMatrix4fv(mUniformMVP, 1, GL_FALSE, glm::value_ptr(proj * view));

    // Perform RenderInterface Rendering
    for (RenderInterface *renderer : mRenderInterfaces)
    {
        renderer->render();
    }

    glfwSwapBuffers(mpWindow);
}

void Application::wrapup(void)
{
    // Perform RenderInterface Wrapup
    for (RenderInterface *renderer : mRenderInterfaces)
    {
        renderer->wrapup();
    }

    // Perform UpdateInterface Wrapup
    for (UpdateInterface *updater : mUpdateInterfaces)
    {
        updater->wrapup();
    }
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
