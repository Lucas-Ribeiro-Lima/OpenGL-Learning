#version 330 core

uniform vec4 ourcolor;

out vec4 FragColor;

void main()
{
	FragColor = ourcolor;
}