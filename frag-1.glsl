#version 330 core

in vec3 VertexColor;
in vec2 TextCoord;

out vec4 FragColor;

uniform sampler2D TextureData;

void main()
{
	FragColor = texture(TextureData, TextCoord);
}