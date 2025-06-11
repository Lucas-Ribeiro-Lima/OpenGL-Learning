#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Instances.h"
#include "Camera.h"

class WindowGl
{
private:
	GLFWwindow* window;
	Camera* cam;
	int height;
	int width;
	int errors;

	float& deltaTime;
	float lastFrame = 0.0f;

	//Mouse controls
	float *w_lastX, *w_lastY, *w_sensitivity, *w_xOffset, *w_yOffset, *w_yaw, *w_pitch;

	//Glad startup;
	void gladConfiguration();

	//Window configuration
	void windowInicialization();
	void processInput(GLFWwindow* window);

	//GLFW start configuration
	void glfwConfiguration();

	void calculateDeltaTime();
public:
	WindowGl(int width, int height, float& deltaVar, Camera* cam);
	void render(std::vector<Instances*> instances);
	int hasErrors();
};

