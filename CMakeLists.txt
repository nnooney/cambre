cmake_minimum_required (VERSION 3.13 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 11)

project(NoonCraft)

# Declare the NoonCraft target
add_executable(nooncraft "")

# Required Packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

# Source Files
target_sources(nooncraft
PUBLIC
    src/render/RenderInterface.cpp
    src/render/TriangleRenderer.cpp
    src/render/CubeRenderer.cpp
    src/utils/CheckError.cpp
    src/ShaderProgram.cpp
    src/Application.cpp
    src/main.cpp)

# Include Directories
target_include_directories(nooncraft
PUBLIC
    src/render/
    src/utils/
    ${OPENGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS})

# Link Libraries
target_link_libraries(nooncraft
    ${OPENGL_gl_LIBRARY}
    ${GLEW_LIBRARIES}
    glfw)
