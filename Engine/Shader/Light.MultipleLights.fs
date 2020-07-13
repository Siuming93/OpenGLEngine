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

struct DirLight {
    // vec3 position; // 使用定向光就不再需要了
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position; 

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct FlashLight {
    vec3 position; 
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform vec3 viewPos;
uniform DirLight dirLight;
uniform PointLight pointLights[4];
uniform FlashLight flashlight;
uniform Material material;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    //漫反射
    vec3 diffuse = dot(normal, lightDir) * light.diffuse;
    //高光
    vec3 reflect = reflect(-lightDir, normal);
    vec3 specular = pow(max(dot(reflect, viewDir), 0.0), material.shininess);
    vec3 ambient = light.ambient; 
}


void main()
{
    vec3 color = texture(material.diffuse, uv).rgb;
    vec3 ambient = light.ambient * color;

    vec3 lightDir = normalize(light.position - FragPos);
    float theta = dot(lightDir, normalize(-light.direction));
   
    if(theta > light.outerCutOff)
    {
        float epsilon   = light.cutOff - light.outerCutOff;
        float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);  

        vec3 specColor = texture(material.specular, uv).rgb;

        float distance = length(FragPos - light.position);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

        vec3 norm = normalize(Normal);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = attenuation * light.diffuse * diff * color;

        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = light.specular * spec * specColor;

        diffuse  *= intensity;
        specular *= intensity;

        vec3 result = (ambient  + diffuse + specular);
        //result = ambient;
        FragColor = vec4(result, 1.0);
    }
    else
    {
        FragColor = vec4(ambient, 1.0);
    }

}