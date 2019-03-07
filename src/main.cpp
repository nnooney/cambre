#include "Application.hpp"
#include "Region.hpp"
#include "InputManager.hpp"
#include "ShaderProgram.hpp"

int main()
{
    Application app;

    ShaderProgram shader(
        "./src/render/shaders/chunk.v.glsl",
        "./src/render/shaders/chunk.f.glsl");

    Region r;
    r.useShader(shader);
    app.addDynamicObject(&r);

    InputManager manager;
    r.getCameraController()->registerWith(&manager);
    app.registerInputs(manager);

    app.printVersionInfo();
    app.run();

    return 0;
}
