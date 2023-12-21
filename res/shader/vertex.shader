#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoord; 
layout (location = 2) in vec3 aColor;

out vec2 v_TexCoord;
out vec3 v_Color;

uniform mat4 t;

void main()
{
    gl_Position = t * vec4(aPosition, 1.0);
    v_TexCoord = aTexCoord;
    v_Color = aColor;
}