#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTextCoord;

out vec2 TextCoord;

uniform mat4 transform;

void main()
{
   gl_Position = transform * vec4(aPos, 1.0);
   TextCoord = aTextCoord;
}