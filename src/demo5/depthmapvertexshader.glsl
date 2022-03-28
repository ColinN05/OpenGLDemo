#version 330 core

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec3 in_Normal;
layout (location = 2) in vec3 in_TexCoords;

uniform mat4 Model;
uniform mat4 LightSpaceMatrix;

void main()
{
    gl_Position = LightSpaceMatrix * Model * vec4(in_Position, 1.0);
}