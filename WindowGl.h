#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GLobject.h"

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
	void render(GLobject* objects[]);
	int hasErrors();
};

