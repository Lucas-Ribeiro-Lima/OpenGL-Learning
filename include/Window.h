#pragma once
#include <GLFW/glfw3.h>
#include <vector>
#include "Instances.h"
#include "Camera.h"

class Window
{
private:
	GLFWwindow* window = nullptr;
  GLFWmonitor* monitor = nullptr;
  const GLFWvidmode* vidmode = nullptr;
	Camera& cam;
	int height = 920;
	int width = 1280;
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
	Window();
	void render(std::vector<Instances> instances);
	int hasErrors();
};

