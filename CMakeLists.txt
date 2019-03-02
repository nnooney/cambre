cmake_minimum_required (VERSION 3.13 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 11)

project(Cambre)

# Declare the Cambre target
add_executable(cambre "")

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

# Directories
set(PROJECT_DIRECTORIES
    src/camera/
    src/commands/
    src/events/
    src/interface/
    src/render/examples/
    src/render/
    src/utils/
    src/world/
    src/)

# Source Files
set(PROJECT_SOURCES
    src/camera/Camera.cpp
    src/camera/CameraController.cpp
    src/commands/CameraCommands.cpp
    src/commands/Command.cpp
    src/events/EventObserver.cpp
    src/interface/LifecycleInterface.cpp
    src/render/examples/TriangleRenderer.cpp
    src/render/examples/CubeRenderer.cpp
    src/utils/CheckError.cpp
    src/utils/PrintVector.cpp
    src/world/Chunk.cpp
    src/world/Region.cpp
    src/Application.cpp
    src/InputManager.cpp
    src/main.cpp
    src/ShaderProgram.cpp)

# Header Files
set(PROJECT_HEADERS
    src/camera/Camera.hpp
    src/camera/CameraController.hpp
    src/commands/CameraCommands.hpp
    src/commands/Command.hpp
    src/events/Event.hpp
    src/events/EventObserver.hpp
    src/interface/DynamicObjectInterface.hpp
    src/interface/LifecycleInterface.hpp
    src/interface/RenderInterface.hpp
    src/interface/UpdateInterface.hpp
    src/render/examples/TriangleRenderer.hpp
    src/render/examples/CubeRenderer.hpp
    src/utils/CheckError.hpp
    src/utils/PrintVector.hpp
    src/utils/Specialization.hpp
    src/world/Block.hpp
    src/world/Chunk.hpp
    src/world/Region.hpp
    src/Application.hpp
    src/ApplicationException.hpp
    src/InputManager.hpp
    src/ShaderProgram.hpp)

# Sources
target_sources(cambre
PUBLIC
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS})

# Include Directories
target_include_directories(cambre
PUBLIC
    ${PROJECT_DIRECTORIES}
    ${OPENGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS})

# Link Libraries
target_link_libraries(cambre
    ${OPENGL_gl_LIBRARY}
    ${GLEW_LIBRARIES}
    glfw)

# Compiler Options
if (UNIX)
    target_compile_options(cambre
    PRIVATE
        -Wall)
endif ()
