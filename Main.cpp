#include "WindowGl.h"
#include "Program.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "GLobject.h"
#include "GLobjectDynamic.h"
#include "Utils.h"
#include <vector>

constexpr auto FRAG_1 = "frag-1.glsl";
constexpr auto VSHADER_1 = "shader-1.glsl";
constexpr auto TEX_EARTH_1 = "assets/grassblockside.png";

std::vector<GLfloat> vertices1 = {

	-0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f, 	0.0f, 0.0f, //0
	 0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f, 	1.0f, 0.0f, //1
	 0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f, 	1.0f, 1.0f, //2
	-0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f, 	0.0f, 1.0f, //3


	-0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 1.0f, 	0.0f, 0.0f, //4
	 0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 1.0f, 	1.0f, 0.0f, //5
	 0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f, 	1.0f, 1.0f, //6
	-0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f, 	0.0f, 1.0f  //7

};

std::vector<GLuint> indices1 = {
	0, 1, 2, //0 Front
	0, 2, 3, //1 Front

	4, 5, 6, //2 Rear
	4, 6, 7, //3 Rear

	4, 0, 3, //4 Face-left
	4, 3, 7, //5 Face-left

	3, 6, 7, //6 Face-up
	2, 3, 6, //7 Face-up

	2, 5, 6, //8 Face-right
	1, 2, 5, //9 Face-right

	0, 4, 5, //10 Bottom
	0, 1, 5, //11 Bottom
};

int main() {

	WindowGl window(800, 600);

	if (window.hasErrors()) return -1;

	Program program1(VSHADER_1, FRAG_1);


	GLobjectDynamic objectDynamic(vertices1, indices1, TEX_EARTH_1, program1);
	objectDynamic.setScale([]() {
		return glm::vec3(0.5f);
	});
	objectDynamic.setRotate([]() {
		return glfwGetTime() * 50.0f;
	}, glm::vec3(1.0f, 1.0f, 1.0f));


	GLobject* objects[2] = { &objectDynamic };

	window.render(objects);

	return 0;
}




