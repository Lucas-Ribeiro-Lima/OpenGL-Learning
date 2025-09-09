#include "WindowGl.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void mouseCallback(GLFWwindow* window, double xPos, double yPos);
void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);

float deltaTime = 0;
float lastFrame = 0;

bool firstMouse = true;
float lastX = 400.0f, lastY = 300.0f;
float sensitivity = 0.1f;
float xOffset = 0.0f;
float yOffset = 0.0f;
float yaw = -90.0f, pitch = 0.0f;

float fov = 1.0f;

enum ERRORS {
	NONE = 0x0000,
	FAIL_CREATE_WINDOW = 0x0001,
	FAIL_INIT_GLAD = 0x0010,
};

WindowGl::WindowGl(int w, int h, Camera* c):  cam(c) {
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
		Utils::logger("Failed to initialize GLAD");
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
		Utils::logger("Failed to create GLFW window");
		errors = FAIL_CREATE_WINDOW;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetScrollCallback(window, scrollCallback);
}

void WindowGl::processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cam->setFrontBack(deltaTime, front);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cam->setFrontBack(deltaTime, back);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cam->setLeftRight(deltaTime, left);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cam->setLeftRight(deltaTime, right);
	}
}

void WindowGl::render(std::vector<Instances> data) {
	while (!glfwWindowShouldClose(window)) {
		calculateDeltaTime();

		cam->update(yaw, pitch, fov);
		processInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (int i = 0; i < data.size(); i++) {
			data[i].drawInstances();
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

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
	fov -= (float) yOffset;

	if (fov < 1.0f) {
		fov = 1.0f;
	}
	if (fov > 45.0f) {
		fov = 45.0f;
	}
}

void WindowGl::calculateDeltaTime() {
	auto currentFrame = static_cast<float>(glfwGetTime());
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}