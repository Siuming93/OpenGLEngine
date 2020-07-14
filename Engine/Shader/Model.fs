#version 330
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 uv;
in vec3 ourColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float     shininess;
};

struct DirLight {
    // vec3 position; // 使用定向光就不再需要了
    vec3 direction;

    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position; 

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

    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];

uniform vec3 viewPos;
uniform DirLight dirLight;
uniform FlashLight flashLight;
uniform Material material;
uniform vec3 ambient;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    //漫反射
    vec3 diffuse = max(0, dot(normal, lightDir))  * light.diffuse;
    //高光
    vec3 reflect = reflect(-lightDir, normal);
    vec3 specular = pow(max(dot(reflect, viewDir), 0.0), material.shininess) * light.specular;

    return diffuse + specular;
}

vec3 CalcPointLight(PointLight light, vec3 fragPos, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    float distance = length(light.position - fragPos);
    float attenuation = 1.0/(light.constant + light.linear * distance + light.quadratic * distance * distance);

    //漫反射
    vec3 diffuse = attenuation * max(0, dot(normal, lightDir))  * light.diffuse;
    //高光
    vec3 reflect = reflect(-lightDir, normal);
    vec3 specular = attenuation * pow(max(dot(reflect, viewDir), 0.0), material.shininess) * light.specular;

    return diffuse +  specular;
}

vec3 CalcFlashLight(FlashLight light, vec3 fragPos, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    float theta = dot(-lightDir, light.direction);
    if(theta >= light.outerCutOff)
    {
        float epsilon   = light.cutOff - light.outerCutOff;
        float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);  

        vec3 lightDir = normalize(light.position - fragPos);
        float distance = length(light.position - fragPos);
        float attenuation = intensity * 1.0/(light.constant + light.linear * distance + light.quadratic * distance * distance);

        //漫反射
        vec3 diffuse = attenuation * max(0, dot(normal, lightDir)) * light.diffuse;
        //高光
        vec3 reflect = reflect(-lightDir, normal);
        vec3 specular = attenuation * pow(max(dot(reflect, viewDir), 0.0), material.shininess) * light.specular;

        return diffuse + specular;
    }
    else
    {
        return vec3(0,0,0);
    }
}


void main()
{
    // 属性
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 color = texture(texture_diffuse1, uv).rgb;

    vec3 light = CalcDirLight(dirLight, norm, viewDir);
    //vec3 light = vec3(0,0,0);
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        light += CalcPointLight(pointLights[i], FragPos, norm, viewDir);
    light += CalcFlashLight(flashLight, FragPos, norm, viewDir);

    vec3 result = (light + ambient + vec3(0.5,0.5,0.5)) * color;

    FragColor = vec4(color, 1.0);

    //FragColor = vec4(ourColor, 1.0);
}