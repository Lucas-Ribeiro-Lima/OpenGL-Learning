#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

in vec2 TextCoord;
in vec3 Normal;
in vec3 FragPosition;

uniform sampler2D TextureData;
uniform vec3 viewPos;

out vec4 FragColor;

void main()
{
    float ambientStrength = 0.1f;
    float specularStrength = 0.5f;

    vec3 lightVector = normalize(vec3(0.0f) - FragPosition);
    vec3 normalVector = normalize(Normal);
    vec3 viewVector = normalize(viewPos - FragPosition);
    vec3 reflectVector = reflect(-lightVector, normalVector);

    float diffuse = max(dot(lightVector, normalVector), 0.0f);
    float specular = pow(max(dot(reflectVector, viewVector), 0.0f), 32) * specularStrength;

	vec4 tex = texture(TextureData, TextCoord);
	FragColor = vec4((ambientStrength + diffuse + specular) * tex.rgb, tex.a);
}