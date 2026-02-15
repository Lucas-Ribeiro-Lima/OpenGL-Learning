#version 330 core
out vec4 FragColor;

struct Material {
  sampler2D diffuse;
  sampler2D specular;
  sampler2D emission;
  float shininess;
};

in vec2 TextCoord;

uniform Material material;
uniform vec3 material_color;

void main()
{
  vec3 textel1 = vec3(texture(material.diffuse, TextCoord));
  FragColor = vec4((textel1 * material_color), 1.0f);
}

