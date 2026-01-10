#include <Engine.h>

namespace oriongl {

Engine::Engine() { windowSystem.setEventBuffer(&inputSystem.getIoEventBufferQueue()); }

void Engine::run() {
    status = ENGINE_RUNNING;
    while (status == ENGINE_RUNNING) {
        inputSystem.processCamera(scene.camera);
        renderSystem.render(scene);
        windowSystem.swapBuffers();

        auto command_buffer = core::getCommandBuffer();

        for (auto &command : command_buffer) {
            if (command.target == core::Target::EngineTarget) {
                if (command.action == core::Action::Quit)
                    status = ENGINE_CLOSING;
            }
        }
    }

    windowSystem.closeWindow();
}

void Engine::loadEntityToScene(std::shared_ptr<graphics::Model> model, std::vector<glm::vec3> instances) {
    core::Entity entity;
    entity.model = std::move(model);
    entity.instances = instances;
    scene.data.push_back(std::move(entity));
}

} // namespace oriongl
