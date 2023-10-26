#version 330 core
layout (location = 0) in vec3 aPos;

out vec2 screenPos;

void main()
{
    gl_Position = vec4(aPos,1.0f);
    screenPos = (aPos.xy+ vec2(1.0f,1.0f))/2;
}