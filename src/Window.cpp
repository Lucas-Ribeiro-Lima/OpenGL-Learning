#include "Window.h"

void framebufferSizeCallback(GLFWwindow *window, int width, int height);

void mouseCallback(GLFWwindow *window, double xPos, double yPos);

void scrollCallback(GLFWwindow *window, double xOffset, double yOffset);

float deltaTime = 0;
float lastFrame = 0;
float mouseX = 0.0f, mouseY = 0.0f, deltaScrollY;

enum ERRORS {
  NONE = 0x0000,
  FAIL_CREATE_WINDOW = 0x0001,
  FAIL_INIT_GLAD = 0x0010,
};

Window::Window() : cam(&getCamera()) {
  errors = NONE;

  glfwConfiguration();

  windowInicialization();
  if ((errors & FAIL_CREATE_WINDOW) == FAIL_CREATE_WINDOW) return;

  gladConfiguration();
  if ((errors & FAIL_INIT_GLAD) == FAIL_INIT_GLAD) return;
}

void Window::gladConfiguration() {
  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    Utils::logger("Failed to initialize GLAD");
    errors = FAIL_INIT_GLAD;
    return;
  }

  glViewport(0, 0, vidmode->width, vidmode->height);
  glEnable(GL_DEPTH_TEST);
}

void Window::glfwConfiguration() {
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
  glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
}

void Window::windowInicialization() {
  monitor = glfwGetPrimaryMonitor();
  vidmode = glfwGetVideoMode(monitor);

  GLFWwindow *w = glfwCreateWindow(vidmode->width, vidmode->height, "LearnOpenGL", nullptr, nullptr);
  window = w;


  if (window == nullptr) {
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

void Window::processInput(GLFWwindow *window) {
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
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    cam->setUpDown(deltaTime, up);
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
    cam->setUpDown(deltaTime, down);
  }
}

void Window::render(std::vector<Instances> &data) {
  while (!glfwWindowShouldClose(window)) {
    calculateDeltaTime();

    cam->update(mouseX, mouseY);
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

int Window::hasErrors() {
  return (errors & (FAIL_CREATE_WINDOW | FAIL_INIT_GLAD)) > 0;
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void mouseCallback(GLFWwindow *window, double xPos, double yPos) {
  mouseX = xPos;
  mouseY = yPos;
}

void scrollCallback(GLFWwindow *window, double xOffset, double yOffset) {
  deltaScrollY = yOffset;
}

void Window::calculateDeltaTime() {
  auto currentFrame = static_cast<float>(glfwGetTime());
  deltaTime = currentFrame - lastFrame;
  lastFrame = currentFrame;
}
