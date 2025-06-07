#include "WindowGl.h"
#include "Program.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "GLobject.h"
#include "Utils.h"
#include <vector>

constexpr auto FRAG_1 = "frag-1.glsl";
constexpr auto VSHADER_1 = "shader-1.glsl";
constexpr auto TEX_EARTH_1 = "assets/grassblockside.png";

std::vector<GLfloat> vertices1 = {
	-0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f, 	0.0f, 0.0f,
	 0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f, 	1.0f, 0.0f,
	 0.5f,  0.5f, 0.0f,    0.0f, 0.0f, 1.0f, 	1.0f, 1.0f,
	-0.5f,  0.5f, 0.0f,    1.0f, 1.0f, 0.0f, 	0.0f, 1.0f
};

std::vector<GLuint> indices1 = {
	0, 1, 2,
	0, 3, 2
};

int main() {

	WindowGl window(800, 600);

	if (window.hasErrors()) return -1;

	Program program1(VSHADER_1, FRAG_1);

	GLobject object1(vertices1, indices1, TEX_EARTH_1, program1);
	GLobject object2(vertices1, indices1, TEX_EARTH_1, program1);
	
	object1.setTranslate(glm::vec3(-0.5f, -0.5f, 0.0f));
	object2.setTranslate(glm::vec3( 0.5f,  0.5f, 0.0f));

	GLobject* objects[2] = { &object1, &object2 };

	window.render(objects);

	return 0;
}




