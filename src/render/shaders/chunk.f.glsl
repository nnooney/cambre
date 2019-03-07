#version 410

in vec4 Color;
out vec4 FragColor;

void main()
{
    FragColor = vec4(
        (int(Color.x) % 16) / 16.0,
        (int(Color.y) % 16) / 16.0,
        (int(Color.z) % 16) / 16.0,
        1.0);
}
