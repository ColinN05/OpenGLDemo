#version 330 core
layout(location = 0) in vec2 Pos;

uniform float Rot;

void main()
{
    // Apply rotation by angle Rot to Pos
    gl_Position = vec4(Pos.x * cos(Rot) + Pos.y * sin(Rot), Pos.x * (-1.0 * sin(Rot)) + Pos.y * cos(Rot), 0.0, 1.0);
}