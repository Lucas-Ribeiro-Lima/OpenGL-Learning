#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Object.h"

class WindowGl
{
private:
	GLFWwindow* window;
	int height;
	int width;
	int errors;

	//Glad startup;
	void gladConfiguration();

	//Window configuration
	void windowInicialization();
	void processInput(GLFWwindow* window);

	//GLFW start configuration
	void glfwConfiguration();

public:
	WindowGl(int width, int height);
	void render(Object* objects[]);
	int hasErrors();
};

