#version 330
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 uv;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float     shininess;
};

struct Light {
    // vec3 position; // 使用定向光就不再需要了
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 viewPos;
uniform Light light;
uniform Material material;

float specularStrength = 0.5;

void main()
{
    vec3 color = texture(material.diffuse, uv).rgb;
    vec3 specColor = texture(material.specular, uv).rgb;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.direction);;

    vec3 ambient = light.ambient * color;

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * color;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * specColor;


    vec3 result = (ambient  + diffuse + specular);
    //result = ambient;
    FragColor = vec4(result, 1.0);
}