#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "CheckError.hpp"

void glCheckError(const char *event)
{
    static bool first = true;
    GLint err = glGetError();
    if (GL_NO_ERROR != err && first == true)
    {
        std::cerr << "GL Error " << err << ": After " << event << std::endl;
        first = false;
    }
}
