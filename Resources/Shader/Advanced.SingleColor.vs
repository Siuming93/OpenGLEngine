#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aColor;

out vec3 ourColor;
out vec2 TexCoord;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};

uniform mat4 model;

void main()
{
    //gl_Position =  vec4(aPos, 1.0);
    gl_Position = projection *  view * model * vec4(aPos, 1.0);
    //ourColor = ( view * vec4(aPos, 1.0f)).rgb;

    TexCoord = aTexCoord;
}