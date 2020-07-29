#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture1;


void main()
{         
    FragColor = texture(ourTexture, TexCoord);

    //FragColor = vec4(ourColor.xyz,1);
    //FragColor = vec4(TexCoord.xy,0,1);    
}


