#include "WindowGl.h"
#include "Program.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "GLSLShaders.h"
#include "GLobject.h"
#include <vector>

std::vector<float> vertices1 = {
	-0.9, -0.5, 0.0,
	-0.3, -0.5, 0.0,
	-0.6,  0.5, 0.0,
};

std::vector<float> vertices2 = {
	 0.9, -0.5, 0.0,
	 0.3, -0.5, 0.0,
	 0.6,  0.5, 0.0
};

std::vector<GLuint> indices1 = {
	0, 1, 2,
};

std::vector<GLuint> indices2 = {
	0, 1, 2,
};

int main() {

	WindowGl window = WindowGl(800, 600);

	if (window.hasErrors()) return -1;

	Program programDefault = Program(GLSLShaders::vShad1, GLSLShaders::vFrag1);
	Program programYellow = Program(GLSLShaders::vShad1, GLSLShaders::vFragYellow);

	GLobject object1 = GLobject(vertices1, indices1, programDefault);
	GLobject object2 = GLobject(vertices2, indices2, programYellow);

	GLobject* objects[2] = { &object1, &object2 };

	window.render(objects);

	return 0;
}




