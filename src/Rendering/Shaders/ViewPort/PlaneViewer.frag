#version 330 core

in vec2 screenPos;

out vec4 FragColor;

uniform vec2 scale;
uniform vec2 offset;

// texture samplers
uniform sampler2D texture1;

void main()
{
    vec2 texCoords = mod ((screenPos*2- offset) / scale,1);
    FragColor = vec4(texCoords.xy, 0f, 1.0f);
    FragColor = texture(texture1, vec2(texCoords.x,-texCoords.y));
}