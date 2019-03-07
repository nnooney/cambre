#version 410

layout (location = 0) in vec4 Position;

uniform mat4 Model;
uniform mat4 ViewProjection;

out vec4 Color;

void main()
{
    gl_Position = ViewProjection * Model * vec4(Position.xyz, 1.0);
    Color = Position;
}
