#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTextCoord; 
layout (location = 2) in vec3 aNormal;

out VS_OUT
{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} vs_out;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    vs_out.FragPos      = vec3(modelMatrix * vec4(aPos, 1.0));
    vs_out.Normal       = normalize(mat3(transpose(inverse(modelMatrix))) * aNormal);
    vs_out.TexCoords    = aTextCoord;

    gl_Position = projectionMatrix * viewMatrix * vec4(vs_out.FragPos, 1.0);
}