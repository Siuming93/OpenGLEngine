#version 330
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 ourColor;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    //gl_Position = vec4(aPos, 1.0);
    ourColor = (model * vec4(aPos, 1.0f)).rgb;
}