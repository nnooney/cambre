cmake_minimum_required (VERSION 3.13 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 11)

project(NoonCraft)

# Declare the NoonCraft target
add_executable(nooncraft "")

# Path Hints to the Packages
if (WIN32)
    set(GLEW_ROOT ${CMAKE_SOURCE_DIR}/lib/glew-2.1.0)
    set(glfw3_ROOT ${CMAKE_SOURCE_DIR}/lib/glfw-3.2.1)
    set(glm_ROOT ${CMAKE_SOURCE_DIR}/lib/glm-0.9.9.3)
elseif (UNIX)
    set(glfw3_ROOT /usr/local/Cellar/glfw/3.2.1)
endif ()

# Required Packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

# Source Files
target_sources(nooncraft
PUBLIC
    src/camera/camera.cpp
    src/camera/CameraController.cpp
    src/commands/CameraCommands.cpp
    src/commands/Command.cpp
    src/events/EventObserver.cpp
    src/render/RenderInterface.cpp
    src/render/examples/TriangleRenderer.cpp
    src/render/examples/CubeRenderer.cpp
    src/utils/CheckError.cpp
    src/utils/PrintVector.cpp
    src/world/Chunk.cpp
    src/ShaderProgram.cpp
    src/InputManager.cpp
    src/Application.cpp
    src/main.cpp)

# Include Directories
target_include_directories(nooncraft
PUBLIC
    src/camera/
    src/commands/
    src/events/
    src/render/examples/
    src/render/
    src/utils/
    src/world/
    src/
    ${OPENGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS})

# Link Libraries
target_link_libraries(nooncraft
    ${OPENGL_gl_LIBRARY}
    ${GLEW_LIBRARIES}
    glfw)
