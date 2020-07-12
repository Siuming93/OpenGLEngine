#version 330
out vec4 FragColor;

in vec3 ourColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    FragColor = vec4(objectColor * lightColor, 1.0);
    //FragColor = vec4(ourColor.xyz,1);
}