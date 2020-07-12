#version 330
out vec4 FragColor;

in vec3 ourColor;
in vec3 FragPos;
in vec3 Normal;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 ambient;
uniform vec3 lightPos;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 result = diffuse * objectColor;
    FragColor = vec4(result, 1.0);
}