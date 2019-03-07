////////////////////////////////////////////////////////////////////////////////
/// @file ShaderProgram.cpp
/// @brief A class to handle GLSL shaders.
///
/// This file contains the GLSL shader class. It is responsible for loading,
/// compiling, and attaching shaders. Each instance of this class contains one
/// vertex shader and one fragment shader.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>
#include <fstream>

#include "ShaderProgram.hpp"
#include "ApplicationException.hpp"

ShaderProgram::ShaderProgram(std::string vertex, std::string fragment)
{
    bool status = false;

    // Construct the Vertex Shader.
    status = useVertexShader(vertex);
    if (status == false)
    {
        throw ApplicationException("Unable to create vertex shader");
    }

    // Construct the Fragment Shader.
    status = useFragmentShader(fragment);
    if (status == false)
    {
        throw ApplicationException("Unable to create fragment shader");
    }

    // Construct the Program.
    status = linkProgram();
    if (status == false)
    {
        throw ApplicationException("Unable to create shader program");
    }
}

ShaderProgram::ShaderProgram(void)
{
    // Set the Compiled and Linked flag to false indicating that a complete
    // program was not made.
    mCompiledAndLinked = false;

    // Set the OpenGL variables.
    mVertexShader = 0;
    mFragmentShader = 0;
    mProgram = 0;
}

ShaderProgram::~ShaderProgram(void)
{
    glDeleteProgram(mProgram);
    glDeleteShader(mVertexShader);
    glDeleteShader(mFragmentShader);
}

bool ShaderProgram::isReadyToUse(void)
{
    // The program is ready to use if it has shaders that have been compiled and
    // linked.
    return mCompiledAndLinked;
}

bool ShaderProgram::useVertexShader(std::string vertex)
{
    GLint glResult = GL_FALSE;

    // By setting a new vertex shader, the program must be relinked in order to
    // use it.
    mCompiledAndLinked = false;

    // If a previous vertex shader exists, then mark it for deletion. OpenGL
    // will not delete the shader until it is no longer in context (i.e. if it
    // is part of the active shader program, it won't get deleted until a new
    // program is used).
    if (mVertexShader != 0)
    {
        glDeleteShader(mVertexShader);
    }

    // Save the filename and source of the file.
    mVertexFile = vertex;
    mVertexSource = readFile(mVertexFile);

    // Construct the new vertex shader.
    mVertexShader = glCreateShader(GL_VERTEX_SHADER);
    if (mVertexShader == 0)
    {
        return false;
    }

    const GLchar *sourceCString = mVertexSource.c_str();
    glShaderSource(mVertexShader, 1, &sourceCString, NULL);
    glCompileShader(mVertexShader);
    glGetShaderiv(mVertexShader, GL_COMPILE_STATUS, &glResult);
    if (GL_FALSE == glResult)
    {
        printInfoLog(mVertexShader);
        glDeleteShader(mVertexShader);
        mVertexShader = 0;
        return false;
    }

    return true;
}

bool ShaderProgram::useFragmentShader(std::string fragment)
{
    GLint glResult = GL_FALSE;

    // By setting a new fragment shader, the program must be relinked in order
    // to use it.
    mCompiledAndLinked = false;

    // If a previous fragment shader exists, then mark it for deletion. OpenGL
    // will not delete the shader until it is no longer in context (i.e. if it
    // is part of the active shader program, it won't get deleted until a new
    // program is used).
    if (mFragmentShader != 0)
    {
        glDeleteShader(mFragmentShader);
    }

    // Save the filename and source of the file.
    mFragmentFile = fragment;
    mFragmentSource = readFile(mFragmentFile);

    // Construct the new fragment shader.
    mFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    if (mFragmentShader == 0)
    {
        return false;
    }

    const GLchar *sourceCString = mFragmentSource.c_str();
    glShaderSource(mFragmentShader, 1, &sourceCString, NULL);
    glCompileShader(mFragmentShader);
    glGetShaderiv(mFragmentShader, GL_COMPILE_STATUS, &glResult);
    if (GL_FALSE == glResult)
    {
        printInfoLog(mFragmentShader);
        glDeleteShader(mFragmentShader);
        mFragmentShader = 0;
        return false;
    }

    return true;
}

bool ShaderProgram::linkProgram(void)
{
    GLint glResult = GL_FALSE;

    // If the program is already compiled and linked (signaling that no new
    // shader has been added), then simply return true.
    if (mCompiledAndLinked == true)
    {
        return true;
    }

    // If either the vertex or the fragment shader is missing, then do not link
    // the program.
    if (mVertexShader == 0 || mFragmentShader == 0)
    {
        return false;
    }

    // Otherwise, we need to relink the program. If a previous program exists,
    // then we mark it for deletion. OpenGL won't delete the program if it is
    // active untile another program is being used.
    if (mProgram != 0)
    {
        glDeleteProgram(mProgram);
    }

    // Construct the new program.
    mProgram = glCreateProgram();
    if (mProgram == 0)
    {
        return false;
    }

    glAttachShader(mProgram, mVertexShader);
    glAttachShader(mProgram, mFragmentShader);
    glLinkProgram(mProgram);
    glGetProgramiv(mProgram, GL_LINK_STATUS, &glResult);
    if (GL_FALSE == glResult)
    {
        printInfoLog(mProgram);
        glDeleteProgram(mProgram);
        mProgram = 0;
        return false;
    }

    // Since the program linked successfully, it is ready to be used.
    mCompiledAndLinked = true;
    return true;
}

void ShaderProgram::use(void)
{
    // Do not activate unless the program is ready.
    if (isReadyToUse() != true)
    {
        std::cerr << "ShaderProgram is not ready to use. Activate failed" <<
            std::endl;
        return;
    }

    glUseProgram(mProgram);
}

GLint ShaderProgram::getProgram(void)
{
    return mProgram;
}

GLuint ShaderProgram::getUniformLocation(std::string uniform)
{
    GLuint loc = glGetUniformLocation(mProgram, uniform.c_str());
    if (loc == GL_INVALID_INDEX)
    {
        std::cerr << "ShaderProgram: unable to find uniform " << uniform <<
            std::endl;
    }
    return loc;
}

ShaderProgram& ShaderProgram::operator=(const ShaderProgram& other)
{
    if (mVertexShader != 0)
    {
        glDeleteShader(mVertexShader);
    }

    if (mFragmentShader != 0)
    {
        glDeleteShader(mFragmentShader);
    }

    if (mProgram != 0)
    {
        glDeleteProgram(mProgram);
    }

    mCompiledAndLinked = other.mCompiledAndLinked;
    mVertexFile = other.mVertexFile;
    mVertexSource = other.mVertexSource;
    mVertexShader = other.mVertexShader;
    mFragmentFile = other.mFragmentFile;
    mFragmentSource = other.mFragmentSource;
    mFragmentShader = other.mFragmentShader;
    mProgram = other.mProgram;

    return *this;
}

std::string ShaderProgram::readFile(std::string filename)
{
    std::ifstream input(filename);
    std::stringstream contents;

    if (input.good())
    {
        contents << input.rdbuf();

        if (contents.good())
        {
            return contents.str();
        }
        else
        {
            std::cerr << "ShaderProgram: Error reading file " << filename <<
                std::endl;
        }
    }
    else
    {
        std::cerr << "ShaderProgram: Unable to locate file " << filename <<
            std::endl;
    }

    return "";
}

void ShaderProgram::printInfoLog(GLint object)
{
    GLint logLength = 0;

    if (glIsShader(object))
    {
        glGetShaderiv(object, GL_INFO_LOG_LENGTH, &logLength);
    }
    else if (glIsProgram(object))
    {
        glGetProgramiv(object, GL_INFO_LOG_LENGTH, &logLength);
    }
    else
    {
        std::cerr << "ShaderProgram::printInfoLog object is not a shader " <<
            "or program)" << std::endl;
        return;
    }

    char * log = new char[logLength];

    if (glIsShader(object))
    {
        glGetShaderInfoLog(object, logLength, NULL, log);
    }
    else if (glIsProgram(object))
    {
        glGetProgramInfoLog(object, logLength, NULL, log);
    }

    std::cerr << "ShaderProgram Info Log:" << std::endl;
    std::cerr << log << std::endl;

    delete[] log;
}
