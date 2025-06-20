#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTextCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TextCoord;
out vec3 VertColor;
out float Brightness;

void main()
{
   gl_Position = projection * view * model * vec4(aPos, 1.0);
   TextCoord = aTextCoord;
   Brightness = 1.0;
   VertColor = aColor;
}