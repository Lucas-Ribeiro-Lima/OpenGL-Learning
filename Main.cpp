#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "WindowGl.h"
#include "Program.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "GLSLShaders.h"
#include "GLobject.h"
#include <iostream>


int main() {

	WindowGl window = WindowGl(800, 600);

	if (window.hasErrors()) return -1;

	GLobject object;

	VertexShader shader = VertexShader(GLSLShaders::vertexShaderSource);
	FragmentShader fragment = FragmentShader(GLSLShaders::fragmentShaderSource);

	Program program = Program(shader, fragment);
	
	window.render(object.getId(), program);

	return 0;
}




