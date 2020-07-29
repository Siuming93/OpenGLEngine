#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture1;


void main()
{         
    vec4 texColor = texture(ourTexture, TexCoord);
    if(texColor.a < 0.1)
        discard;
    FragColor = texColor;
    //FragColor = vec4(ourColor.xyz,1);
    //FragColor = vec4(TexCoord.xy,0,1);    
}


