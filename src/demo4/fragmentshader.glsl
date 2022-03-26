#version 330 core

in vec2 ex_TexCoords;

out vec4 FragColor;

uniform sampler2D Texture;

void main()
{
    FragColor = texture(Texture, ex_TexCoords);
}