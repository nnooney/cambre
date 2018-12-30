#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLFWwindow *app = nullptr;

bool initializeGL(void)
{
    // Initialize GLFW library
    if (!glfwInit())
    {
        // Initialization Failed
        return false;
    }

    // Construct a GL Context by creating a window.
    app = glfwCreateWindow(640, 480, "Nooncraft", NULL, NULL);
    if (!app)
    {
        // Creation Failed
        return false;
    }
    glfwMakeContextCurrent(app);

    // Initialzie GLEW library. Requires a GL Context from an application window
    // first.
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        // Initialization Failed
        return false;
    }

    return true;
}

void displayGLSettings(void)
{
    int major, minor, revision;

    // GLFW
    glfwGetVersion(&major, &minor, &revision);
    std::cout << "GLFW: " << major << "." << minor << "." << revision << std::endl;

    // OpenGL
    std::cout << "GL: " << glGetString(GL_VERSION) << std::endl;
}

bool terminateGL(void)
{
    // Destroy the created window
    glfwDestroyWindow(app);

    // Terminate GLFW library
    glfwTerminate();

    return true;
}

int main()
{
    bool status = initializeGL();

    if (!status)
    {
        std::cerr << "An initialization error has occurred ..." << std::endl;
        return 1;
    }

    displayGLSettings();

    terminateGL();

    return 0;
}
