#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture1;

float near = 0.1; 
float far  = 100.0; 

float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));    
}

void main()
{         
    FragColor = mix(texture(ourTexture, TexCoord), texture(ourTexture1, TexCoord), 0.2);
    FragColor = vec4(vec3(gl_FragCoord.z), 1.0);
    //FragColor = vec4(ourColor.xyz,1);
    //FragColor = vec4(TexCoord.xy,0,1);    
    float depth = LinearizeDepth(gl_FragCoord.z) / far; // 为了演示除以 far
    FragColor = vec4(vec3(depth), 1.0);
}


