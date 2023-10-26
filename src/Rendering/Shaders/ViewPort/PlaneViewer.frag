#version 330 core

in vec2 screenPos;

out vec4 FragColor;

uniform vec2 size;

void main()
{
    vec2 texCoords = mod (screenPos+ vec2(0.25f),0.5f)*2.0f ;
    FragColor = vec4(texCoords.xy, 0f, 1.0f);
}