#include "WindowGl.h"
#include "Object.h"
#include "ObjectDynamic.h"
#include "Program.h"
#include "FragmentShader.h"
#include "VertexShader.h"
#include "Texture.h"
#include "Geometry.h"
#include "Utils.h"
#include <vector>

constexpr auto VSHADER_1 = "shader-1.glsl";
constexpr auto FRAG_1 = "frag-1.glsl";
constexpr auto TEX_EARTH_1 = "assets/grassblockside.png";

std::vector<GLfloat> vertexesCube = {

	-0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f, 	0.0f, 0.0f, //0
	 0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f, 	1.0f, 0.0f, //1
	 0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f, 	1.0f, 1.0f, //2
	-0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f, 	0.0f, 1.0f, //3


	-0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 1.0f, 	0.0f, 0.0f, //4
	 0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 1.0f, 	1.0f, 0.0f, //5
	 0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f, 	1.0f, 1.0f, //6
	-0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f, 	0.0f, 1.0f  //7

};

std::vector<GLuint> indexesCube = {
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

	//Default Geometrics and Textures
	Geometry CUBE_GEOMETRY(vertexesCube, indexesCube);
	Texture TEX_GRASS_CUBE(TEX_EARTH_1);

	//Default Program
	Program DEF_PROGRAM(VSHADER_1, FRAG_1);

	ObjectDynamic object(CUBE_GEOMETRY, &TEX_GRASS_CUBE, DEF_PROGRAM);
	object.setScale([]() {
		return glm::vec3(0.5f);
	});
	object.setRotate([]() {
		return glfwGetTime() * 50.0f;
	}, glm::vec3(1.0f, 1.0f, 1.0f));


	Object* objects[2] = { &object };

	window.render(objects);

	return 0;
}




