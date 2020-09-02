#version 330 core
out vec4 FragColor;

in vec3 fColor;
in vec2 uv;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;

void main()
{
    vec3 color = texture(texture_diffuse1, uv).rgb;
    FragColor = vec4(color, 1.0);
}