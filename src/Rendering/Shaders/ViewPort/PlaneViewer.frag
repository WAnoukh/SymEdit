#version 330 core

in vec2 screenPos;

out vec4 FragColor;

uniform vec2 scale;
uniform vec2 offset;

// texture samplers
uniform sampler2D texture1;

void main()
{
    vec2 temp = (screenPos*2) / scale + offset;
    vec2 texCoords = mod (temp,1);
    if (temp.x < 1 && temp.x > 0 && temp.y < 1 && temp.y > 0){
        FragColor = vec4(1.0f,1.0f,0.0f,1.0f);
    }else{
        FragColor = vec4(texCoords.xy, 0f, 1.0f);
    }
    //FragColor = texture(texture1, vec2(texCoords.x,-texCoords.y));
}