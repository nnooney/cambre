#include "Application.hpp"
#include "ShaderProgram.hpp"
#include "TriangleRender.hpp"

int main()
{
    Application app;

    ShaderProgram shader(
        "./src/shaders/default.v.glsl",
        "./src/shaders/default.f.glsl");
    app.useShader(shader);

    TriangleRender triangle;
    app.addRenderer(&triangle);

    app.printVersionInfo();
    app.run();

    return 0;
}
