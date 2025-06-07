#version 330 core

in vec2 TextCoord;

out vec4 FragColor;

uniform sampler2D TextureData;

void main()
{
	FragColor = texture(TextureData, TextCoord);
}