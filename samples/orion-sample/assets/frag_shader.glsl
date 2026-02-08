#version 330 core
struct LightScaling {
    float ambient;
    float diffuse;
    float specular;
};

struct Light {
  vec4 position;
  vec4 direction;
  vec3 color;
  float cutOff;
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

uniform Light directional;
uniform LightScaling lightScaling;
uniform Material material;
uniform vec3 viewPos;

out vec4 FragColor;

void main()
{
  vec4 textel1 = texture(material.diffuse, TextCoord);
  vec4 textel2 = texture(material.specular, TextCoord);

  vec3 diffTextelRGB = textel1.rgb;
  vec3 specTextelRGB = textel2.rgb;
  vec3 ambientColor = diffTextelRGB * lightScaling.ambient; 

  vec3 lightVector = normalize(vec3(-directional.direction));
  vec3 normalVector = normalize(NormalPos);
  float diffuseFactor = max(dot(lightVector, normalVector), 0.0);

  vec3 diffuseColor = lightScaling.diffuse * (diffuseFactor * diffTextelRGB);
  // vec3 diffuseColor = diffuseFactor * diffTextelRGB;

  vec3 specularVector = normalize(viewPos - FragPos);
  vec3 reflectedVector = reflect(-lightVector, normalVector);
  float specularFactor = pow(max(dot(reflectedVector, specularVector), 0.0), 32);

  vec3 specularColor = lightScaling.specular * (specularFactor * specTextelRGB);

  vec3 finalColor = ambientColor + diffuseColor + specularColor;
  float alpha = textel1.a + textel2.a;
  FragColor = vec4(finalColor, alpha);
}

