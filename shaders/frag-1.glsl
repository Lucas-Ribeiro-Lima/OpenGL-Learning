#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec2 TextCoord;
in vec3 Normal;
in vec3 FragPosition;
uniform vec3 viewPos;

uniform Light light;
uniform Material material;

out vec4 FragColor;

void main()
{
    vec4 textel = texture(material.diffuse, TextCoord);
    vec3 texDiff= textel.rgb;
    float texAlpha = textel.a;

    //Ambient light;
    vec3 ambientColor = light.ambient * texDiff;

    //Diffuse calc
    vec3 lightVector = normalize(light.position - FragPosition);
    vec3 normalVector = normalize(Normal);
    float diffuseFactor = max(dot(lightVector, normalVector), 0.0f);
    vec3 diffuseColor = light.diffuse * (diffuseFactor * texDiff);

    //Specular calc
    vec3 viewVector = normalize(viewPos - FragPosition);
    vec3 reflectVector = reflect(-lightVector, normalVector);
    float specularFactor = pow(max(dot(reflectVector, viewVector), 0.0f), 32);
    vec3 specularColor = light.specular * (specularFactor * texDiff) * vec3(0.0f);

    vec3 fragColor = ambientColor + diffuseColor + specularColor;
	FragColor = vec4(fragColor, texAlpha);
}