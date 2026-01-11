#pragma once

// clang-format off
#include <glad.h>
#include <GLFW/glfw3.h>
// clang-format on
#include <InputSystemForward.h>

namespace oriongl::core {
class WindowSystem {
  public:
    WindowSystem();

    void setTitle(const char *title);
    void swapBuffers();
    void closeWindow();
    void update();

  private:
    GLFWwindow *window = nullptr;
    GLFWmonitor *monitor = nullptr;
    const GLFWvidmode *vidmode = nullptr;

    int width = 1280;
    float deltaTime = 0;
    float lastFrame = 0;

    // Glad configuration;
    void gladConfiguration();

    // Window configuration
    void windowInicialization();

    void processInput(GLFWwindow *window);

    // GLFW start configuration
    void glfwConfiguration();

    void calculateDeltaTime();

    static void mouseCallback(GLFWwindow *window, double xPos, double yPos);

    static void keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

    static void framebufferSizeCallback(GLFWwindow *window, int width, int height);
};
} // namespace oriongl::core
