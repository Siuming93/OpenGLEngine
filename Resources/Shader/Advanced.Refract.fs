#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos; 

uniform samplerCube skybox;
uniform vec3 cameraPos;

void main()
{    
    float ratio = 1.00 / 1.52;
    vec3 I = normalize(FragPos - cameraPos);
    vec3 R = refract(I, normalize(Normal), ratio);
    FragColor = texture(skybox, R);
}