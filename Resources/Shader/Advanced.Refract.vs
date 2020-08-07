#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

out vec3 FragPos;  
out vec3 Normal;  

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};
uniform mat4 model;

void main()
{
    vec4 pos = Matrices.projection * Matrices.view *model* vec4(aPos, 1.0);
    FragPos = (model * vec4(aPos, 1.0)).xyz;
    Normal = normal;
    gl_Position = pos.xyzw;
}