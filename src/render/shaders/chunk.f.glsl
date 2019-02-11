#version 410

in vec4 Color;
out vec4 FragColor;

void main()
{
    FragColor = vec4(Color.x / 16.0, Color.y / 16.0, Color.z / 16.0, 1.0);
}
