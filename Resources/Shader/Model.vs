#version 330
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;
layout (location = 3) in vec3 tangent;
layout (location = 3) in vec3 Bitangent;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 ourColor;
out vec3 Normal;
out vec3 FragPos;  
out vec2 uv;


void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    //gl_Position = vec4(aPos, 1.0);
    ourColor = (projection * view * model * vec4(aPos, 1.0)).xyz;
    FragPos = (model * vec4(aPos, 1.0)).xyz;
    Normal = mat3(transpose(inverse(model))) * aNormal;
    uv = aUV;
}