#include "WindowGl.h"
#include "Program.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "GLobject.h"
#include "Utils.h"
#include <vector>


#define FRAG_RED "fShaderRed.glsl"
#define FRAG_YEL "fShaderYellow.glsl"
#define VSHADER_1 "vShader1.glsl"


std::vector<float> vertices1 = {
	-0.9, -0.5, 0.0,    0.0, 0.0, 0.6,
	-0.3, -0.5, 0.0,    0.0, 1.0, 1.0,
	-0.6,  0.5, 0.0,    0.0, 0.0, 0.6
};

std::vector<float> vertices2 = {
	 0.9, -0.5, 0.0,    1.0, 0.0, 0.6,
	 0.3, -0.5, 0.0,    0.0, 1.0, 1.0,
	 0.6,  0.5, 0.0,    1.0, 0.0, 0.6
};

std::vector<GLuint> indices1 = {
	0, 1, 2,
};

std::vector<GLuint> indices2 = {
	0, 1, 2,
};


int main() {

	WindowGl window(800, 600);

	if (window.hasErrors()) return -1;

	Program program1(VSHADER_1, FRAG_RED);
	Program program2(VSHADER_1, FRAG_YEL);

	GLobject object1(vertices1, indices1, program1);
	GLobject object2(vertices2, indices2, program2);

	GLobject* objects[2] = { &object1, &object2 };

	window.render(objects);

	return 0;
}




