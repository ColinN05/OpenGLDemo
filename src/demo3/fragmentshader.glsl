#version 330 core

out vec4 FragColor;

in vec4 ex_Pos;

void main()
{
    float fade = max(0.0, 1.0 - 1.0 * length(ex_Pos.xy));
    FragColor = fade * sdfsad vec4(0.6, 0.65, 0.28, 1.0);
}