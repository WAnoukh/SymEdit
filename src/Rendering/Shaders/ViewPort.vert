#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform vec2 scale;

void main()
{
	gl_Position = vec4(aPos * vec3(scale,1.0), 1.0);
	ourColor = vec3(aTexCoord,0.0);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}