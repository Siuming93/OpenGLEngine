#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;  

uniform samplerCube skybox;
uniform vec3 cameraPos;

void main()
{    
    vec3 I = normalize(FragPos - cameraPos);
    vec3 R = reflect(I, normalize(Normal));
    FragColor = texture(skybox, R);
}