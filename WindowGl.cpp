#include "WindowGl.h"
#include <iostream>

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

enum ERRORS {
	NONE = 0x0000,
	FAIL_CREATE_WINDOW = 0x0001,
	FAIL_INIT_GLAD = 0x0010,
};

WindowGl::WindowGl(int w = 800, int h = 600) {
	width = w;
	height = h;
	errors = NONE;
	
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
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void WindowGl::glfwConfiguration() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

void WindowGl::windowInicialization() {
	GLFWwindow* w = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	window = w;

	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		errors = FAIL_CREATE_WINDOW;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
}

void WindowGl::processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void WindowGl::render(Object* objects[]) {
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		int len = 1;
		for (int i = 0; i < len; i++) {
			objects[i]->draw();
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
