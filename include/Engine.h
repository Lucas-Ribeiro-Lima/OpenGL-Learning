#pragma once

// clang-format off
#include <WindowSystem.h>
// clang-format on

#include <InputSystem.h>
#include <RenderSystem.h>
#include <ResourceSystem.h>
#include <Scene.h>

namespace oriongl {

enum EngineStatus {
    ENGINE_RUNNING,
    ENGINE_CLOSING,
    ENGINE_STOPPED,
};

class Engine {
  private:
    core::WindowSystem windowSystem;
    core::ResourceSystem resourceSystem;
    core::RenderSystem renderSystem;
    core::InputSystem inputSystem;

    core::Scene scene;

    EngineStatus status = ENGINE_STOPPED;

  public:
    Engine();
    void run();
    void loadEntityToScene(std::shared_ptr<graphics::Model> model, std::vector<glm::vec3> instances);
};

} // namespace oriongl
