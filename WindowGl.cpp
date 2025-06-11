#include "WindowGl.h"
#include <iostream>

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void mouseCallback(GLFWwindow* window, double xPos, double yPos);

float lastX = 400.0f, lastY = 300.0f;
float sensitivity = 0.1f;
float xOffset = 0.0f;
float yOffset = 0.0f;
float yaw = -90.0f, pitch = 0.0f;

bool firstMouse = true;


enum ERRORS {
	NONE = 0x0000,
	FAIL_CREATE_WINDOW = 0x0001,
	FAIL_INIT_GLAD = 0x0010,
};

WindowGl::WindowGl(int w, int h, float& d, Camera* c): deltaTime(d), cam(c) {
	width = w;
	height = h;
	errors = NONE;

	w_lastX = &lastX;
	w_lastY = &lastY;
	w_sensitivity = &sensitivity;
	w_xOffset = &xOffset;
	w_yOffset = &yOffset;
	w_pitch = &pitch;
	w_yaw = &yaw;

	glfwConfiguration();

	windowInicialization();
	if ((errors & FAIL_CREATE_WINDOW) == FAIL_CREATE_WINDOW) return;

	gladConfiguration();
	if ((errors & FAIL_INIT_GLAD) == FAIL_INIT_GLAD) return;
}

void WindowGl::gladConfiguration() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		errors = FAIL_INIT_GLAD;
		return;
	}

	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
}

void WindowGl::glfwConfiguration() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

void WindowGl::windowInicialization() {
	GLFWwindow* w = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
	window = w;

	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		errors = FAIL_CREATE_WINDOW;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouseCallback);
}

void WindowGl::processInput(GLFWwindow* window) {
	float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cam->setFrontBack(cameraSpeed, front);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cam->setFrontBack(cameraSpeed, back);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cam->setLeftRight(cameraSpeed, left);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cam->setLeftRight(cameraSpeed, right);
	}
}

void WindowGl::render(std::vector<Instances*> data) {
	while (!glfwWindowShouldClose(window)) {
		calculateDeltaTime();
		processInput(window);
		cam->updateFront(yaw, pitch);

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (int i = 0; i < data.size(); i++) {
			data[i]->drawInstances();
		}

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
}

int WindowGl::hasErrors() {
	return (errors & (FAIL_CREATE_WINDOW | FAIL_INIT_GLAD)) > 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void mouseCallback(GLFWwindow* window, double xPos, double yPos) {
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	xOffset = xPos - lastX;
	yOffset = lastY - yPos;

	lastX = xPos;
	lastY = yPos;

	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}
}

void WindowGl::calculateDeltaTime() {
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}