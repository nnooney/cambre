////////////////////////////////////////////////////////////////////////////////
/// @file ShaderProgram.hpp
/// @brief A class to handle GLSL shaders.
///
/// This file contains the GLSL shader class. It is responsible for loading,
/// compiling, and attaching shaders. Each instance of this class contains one
/// vertex shader and one fragment shader.
////////////////////////////////////////////////////////////////////////////////

#ifndef _CAMBRE_SHADER_PROGRAM_H_
#define _CAMBRE_SHADER_PROGRAM_H_

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

/// @class ShaderProgram
/// @brief A class to handle GLSL shaders.
///
/// The Shader Program Class contains methods for reading, compiling, and
/// linking a GLSL Shader Program.
class ShaderProgram
{
public:
    /// @brief The constructor.
    ///
    /// At construction time, the files representing the vertex and fragment
    /// shaders are read in and compiled and a Program is made and linked. If
    /// any error occurs here, an ApplicationException is thrown.
    ShaderProgram(std::string vertex, std::string fragment);

    /// @brief The default constructor.
    ///
    /// This creates an empty Shader Program. It is unable to be used until a
    /// vertex and fragment shader are added to it and a program is made via
    /// the linkProgram method.
    ShaderProgram(void);

    /// @brief The default destructor.
    ///
    /// This will free the OpenGL resources.
    ~ShaderProgram(void);

    /// @brief Determines if the Program is ready to be used.
    ///
    /// A Program is ready to be used if it has been compiled and linked, which
    /// is the status of the mCompiledAndLinked member variable.
    ///
    /// @returns True if the program has been compiled and linked or false if it
    /// has not been either compiled or linked.
    bool isReadyToUse(void);

    /// @brief Sets up and compiles a vertex shader.
    ///
    /// This function will read the source of the file 'vertex' and compile it.
    /// Only one vertex shader can be associated with the shader program. If a
    /// previous vertex shader has been created, then it will be overwritten by
    /// the new one.
    ///
    /// @attention Creating a new shader requires the program to be relinked.
    /// @returns True if creation and compilation was successful or false if an
    /// error occured.
    bool useVertexShader(std::string vertex);

    /// @brief Sets up and compiles a fragment shader.
    ///
    /// This function will read the source of the file 'fragment' and compile
    /// it. Only one fragment shader can be associated with the shader program.
    /// If a previous fragment shader has been created, then it will be
    /// overwritten by the new one.
    ///
    /// @attention Creating a new shader requires the program to be relinked.
    /// @returns True if creation and compilation was successful or false if an
    /// error occured.
    bool useFragmentShader(std::string fragment);

    /// @brief Sets up and links the program with the already existing shaders.
    ///
    /// This function will attach the fragment and vertex shader and link it
    /// into a compiled program ready for use.
    ///
    /// @returns True if linking was successful or false if an error occured.
    bool linkProgram(void);

    /// @brief Activeates the Program for use in the OpenGL pipeline.
    ///
    /// This function will make the ShaderProgram the active program.
    void use(void);

    /// @brief Gets the program variable for use with OpenGL render functions.
    ///
    /// This function is a getter for mProgram.
    GLint getProgram(void);

    /// @brief Gets the location of a uniform in the program.
    ///
    /// The function retrieves a uniform location in the program.
    GLuint getUniformLocation(std::string uniform);

    /// @brief The overloaded assignment operator.
    ///
    /// Copies the contents of one shader program to another.
    ShaderProgram& operator=(const ShaderProgram& other);

private:
    /// @brief A flag indicating a complete program was created.
    bool mCompiledAndLinked;

    /// @brief The file used to compile the Vertex Shader.
    std::string mVertexFile;

    /// @brief The Vertex Shader source.
    std::string mVertexSource;

    /// @brief The OpenGL Compiled Vertex Shader.
    GLint mVertexShader;

    /// @brief The file used to compile the Fragment Shader.
    std::string mFragmentFile;

    /// @brief The Fragment Shader source.
    std::string mFragmentSource;

    /// @brief The OpenGL Compiled Fragment Shader.
    GLint mFragmentShader;

    /// @brief The OpenGL Linked Shader Program.
    GLint mProgram;

    /// @brief A helper function to read the contents of a file.
    ///
    /// This function reads the contents of the file passed in as an argument
    /// and returns the contents of that file as a string.
    ///
    /// @returns The contents of filename.
    std::string readFile(std::string filename);

    /// @brief Prints the OpenGL Log when an error is detected.
    ///
    /// This function will print the contents of the OpenGL Info Log when
    /// something bad has happened.
    void printInfoLog(GLint object);
};

#endif
