#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Instances.h"
#include "Camera.h"
#include "ResourceManager.h"

class WindowGl
{
private:
	GLFWwindow* window;
	Camera* cam;
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

	void calculateDeltaTime();
public:
	WindowGl(int width, int height, Camera* cam);
	void render(std::vector<Instances*> instances);
	int hasErrors();
};

