#include <Engine.h>

namespace oriongl {

void Engine::run() {
    status = ENGINE_RUNNING;
    while (status == ENGINE_RUNNING) {
        inputSystem.process();
        renderSystem.render(scene);
        windowSystem.swapBuffers();

        processCommands();
        inputSystem.cleanup();
    }

    windowSystem.closeWindow();
}

void Engine::processCommands() {
    auto command_buffer = core::getCommands();

    for (auto &command : command_buffer) {
        if (command.action == core::Action::Quit) {
            status = ENGINE_CLOSING;
        }
    }
}

void Engine::loadEntityToScene(std::shared_ptr<graphics::Model> model, std::vector<glm::vec3> instances) {
    core::Entity entity;
    entity.model = std::move(model);
    entity.instances = instances;
    scene.data.push_back(std::move(entity));
}

} // namespace oriongl
