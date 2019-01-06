#version 410

layout (location = 0) in vec3 pos;

void main(void)
{
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
}
