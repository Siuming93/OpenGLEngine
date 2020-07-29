#version 330

out vec4 FragColor;

in vec2 uv;

uniform vec3 lightColor;

void main()
{
    FragColor = vec4(lightColor, 1.0);
    //FragColor = vec4(uv, 0, 1.0);
}