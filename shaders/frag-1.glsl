#version 330 core

in vec2 TextCoord;
out vec4 FragColor;

uniform sampler2D TextureData;

void main()
{
	vec3 lightColor = vec3(0.5f, 0.0f, 0.0f);
	vec4 tex = texture(TextureData, TextCoord);

	FragColor = vec4(tex.rgb * lightColor, tex.a);
}