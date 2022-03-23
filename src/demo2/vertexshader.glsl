#version 330 core
layout(location = 0) in vec2 Pos;
layout(location = 1) in vec3 Color;

out vec4 color;

void main()
{
    color = vec4(Color, 1.0);
    gl_Position = vec4(Pos, 0.0, 1.0);
}