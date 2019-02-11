#include "Application.hpp"
#include "ShaderProgram.hpp"
#include "TriangleRenderer.hpp"
#include "CubeRenderer.hpp"
#include "Chunk.hpp"
#include "InputManager.hpp"

int main()
{
    Application app;

    ShaderProgram shader(
        "./src/render/shaders/chunk.v.glsl",
        "./src/render/shaders/chunk.f.glsl");
    app.useShader(shader);

    Chunk chunk;
    app.addRenderer(&chunk);

    InputManager manager;
    app.registerInputs(manager);

    app.printVersionInfo();
    app.run();

    return 0;
}
