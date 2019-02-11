#version 410

layout (location = 0) in vec4 Position;

uniform mat4 MVP;

out vec4 Color;

void main()
{
    gl_Position = MVP * vec4(Position.xyz, 1.0);
    Color = Position;
}
