#version 330 core

in vec2 TextCoord;
in vec3 VertColor;
in float Brightness;

out vec4 FragColor;

void main()
{
	float bright = Brightness * Brightness;
	FragColor = vec4(VertColor, bright);
}