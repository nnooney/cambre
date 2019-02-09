#include "Application.hpp"
#include "ShaderProgram.hpp"
#include "TriangleRenderer.hpp"
#include "CubeRenderer.hpp"
#include "InputManager.hpp"

int main()
{
    Application app;

    ShaderProgram shader(
        "./src/render/shaders/vertex.glsl",
        "./src/render/shaders/fragment.glsl");
    app.useShader(shader);

    CubeRenderer cube;
    app.addRenderer(&cube);

    InputManager manager;
    app.registerInputs(manager);

    app.printVersionInfo();
    app.run();

    return 0;
}
