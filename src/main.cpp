#include "Application.hpp"
#include "ShaderProgram.hpp"
#include "TriangleRenderer.hpp"
#include "CubeRenderer.hpp"

int main()
{
    Application app;

    ShaderProgram shader(
        "./src/shaders/vertex.glsl",
        "./src/shaders/fragment.glsl");
    app.useShader(shader);

    CubeRenderer cube;
    app.addRenderer(&cube);

    app.printVersionInfo();
    app.run();

    return 0;
}
