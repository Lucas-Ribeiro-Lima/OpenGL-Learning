#version 330 core
struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
  sampler2D diffuse;
  sampler2D specular;
  sampler2D emission;
  float shininess;
};

in vec3 FragPos;
in vec3 NormalPos;
in vec2 TextCoord;

uniform Light light;
uniform Material material;
uniform vec3 viewPos;

out vec4 FragColor;

void main()
{
  vec4 textel1 = texture(material.diffuse, TextCoord);
  if(textel1.a < 0.1)
    discard;

  vec4 textel2 = texture(material.specular, TextCoord);

  vec3 diffTextelRGB = textel1.rgb;
  vec3 specTextelRGB = textel2.rgb;
  vec3 ambientColor = diffTextelRGB * light.ambient; 

  vec3 lightVector = normalize(light.position - FragPos);
  vec3 normalVector = normalize(NormalPos);
  float diffuseFactor = max(dot(lightVector, normalVector), 0.0);

  vec3 diffuseColor = light.diffuse * (diffuseFactor * diffTextelRGB);

  vec3 specularVector = normalize(viewPos - FragPos);
  vec3 reflectedVector = reflect(-lightVector, normalVector);
  float specularFactor = pow(max(dot(reflectedVector, specularVector), 0.0), 32);

  vec3 specularColor = light.specular * (specularFactor * specTextelRGB);

  vec3 finalColor = ambientColor + diffuseColor + specularColor;
  float alpha = textel1.a + textel2.a;
  FragColor = vec4(finalColor, alpha);
}

