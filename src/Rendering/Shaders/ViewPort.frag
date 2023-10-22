#version 330 core

in vec2 TexCoord;


out vec4 FragColor;

// texture samplers
uniform sampler2D texture1;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragColor = mix (texture(texture1, TexCoord), vec4(TexCoord.x, TexCoord.y,0,0), 0.5);
	//FragColor = vec4(TexCoord.x, TexCoord.y,0,0);
}