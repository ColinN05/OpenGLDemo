#version 330 core

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec3 in_Normal;
layout (location = 2) in vec2 in_TexCoords;

out vec4 ex_Normal;
out vec2 ex_TexCoords;
out vec4 ex_LightDirection;
out vec4 ex_FragPos;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 LightDirection;

void main()
{
    gl_Position = Projection * View * Model * vec4(in_Position, 1.0);
    ex_Normal = vec4(normalize(mat3(transpose(inverse(Model))) * in_Normal), 1.0);
    ex_TexCoords = in_TexCoords;
    ex_LightDirection = normalize(-1.0 * vec4(LightDirection, 0.0));
    ex_FragPos = View * Model * vec4(in_Position, 1.0);
}