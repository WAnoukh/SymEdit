#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform vec2 scale;
uniform vec2 offset;
uniform float time;

void main()
{
	gl_Position = vec4(aPos * vec3(scale,1.0), 1.0) + vec4(offset,0.0f,0.0f) ; //+ vec4(sin(time + aPos.x)/2.0,0.0,0.0,0.0)
	TexCoord = aTexCoord;
}