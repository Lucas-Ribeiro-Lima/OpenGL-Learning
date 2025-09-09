#version 330 core

in vec2 TextCoord;
in vec3 Normal;
in vec3 FragPosition;

uniform sampler2D TextureData;

out vec4 FragColor;

void main()
{
    vec3 lightVector = normalize(vec3(0.0f) - FragPosition);
    vec3 normalVector = normalize(Normal);

    float ambientLight = 0.1f;
    float diffuse = max(dot(lightVector, normalVector), 0.0f);
	vec4 tex = texture(TextureData, TextCoord);

	FragColor = vec4((ambientLight + diffuse ) * tex.rgb, tex.a);
}