#include "WindowGl.h"
#include "Program.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "GLobject.h"
#include "Utils.h"
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

std::string fRed = Utils::readShader("fShaderRed.glsl");
std::string fYellow = Utils::readShader("fShaderYellow.glsl");
std::string vShader = Utils::readShader("vShader1.glsl");

int main() {

	WindowGl window(800, 600);

	if (window.hasErrors()) return -1;

	Program programDefault(vShader, fRed);
	Program programYellow(vShader, fYellow);

	GLobject object1(vertices1, indices1, programDefault);
	GLobject object2(vertices2, indices2, programYellow);

	GLobject* objects[2] = { &object1, &object2 };

	window.render(objects);

	return 0;
}




