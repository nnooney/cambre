#include "Application.hpp"
#include "CameraController.hpp"
#include "InputManager.hpp"
#include "Region.hpp"
#include "ShaderProgram.hpp"

int main()
{
    Application app;
    CameraController cc;
    ShaderProgram shader(
        "./src/render/shaders/chunk.v.glsl",
        "./src/render/shaders/chunk.f.glsl");
    Region r;
    InputManager manager;

    r.useShader(shader);
    r.useCameraController(cc);
    r.registerWith(manager);

    app.registerInputs(manager);
    app.addDynamicObject(&r);

    app.printVersionInfo();
    app.run();

    return 0;
}
