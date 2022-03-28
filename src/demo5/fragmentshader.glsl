#version 330 core

in vec4 ex_Normal;
in vec2 ex_TexCoords;
in vec4 ex_LightDirection;
in vec4 ex_FragPos;

out vec4 FragColor;

uniform sampler2D Texture;
uniform sampler2D DepthMap;
uniform mat4 LightProjectionMatrix;

void main()
{
    vec4 ambient = vec4(0.2, 0.2, 0.2, 0.1) * texture(Texture, ex_TexCoords);
    vec4 norm = normalize(ex_Normal);
    vec4 diffuse = max(0.0, dot(norm, normalize(ex_LightDirection))) * texture(Texture, ex_TexCoords);

    vec4 projCoords = LightProjectionMatrix * ex_FragPos;
    float compareDepth = texture(DepthMap, projCoords.xy).r;
    float fragDepth = projCoords.z;
    if (compareDepth == 0.0)
    {
        //diffuse = vec4(1.0,0.0,0.0,1.0);
    }
    FragColor = ambient + diffuse;
}