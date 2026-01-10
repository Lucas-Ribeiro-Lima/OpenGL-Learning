#include <InputLayer.h>
#include <InputSystem.h>

namespace {
oriongl::core::CommandBuffer commandBuffer;
}

namespace oriongl::core {
InputSystem::InputSystem() {};

void InputSystem::processCamera(Camera &camera) {
    for (auto &event : raw_io_event_buffer) {
        if (input::KeyTranslationLayer::getKey(event.data[0]) == input::Key::Escape)
            commandBuffer.push_back(Command{Target::EngineTarget, Action::Quit});
    }

    raw_io_event_buffer.clear();
}

EventBuffer &InputSystem::getIoEventBufferQueue() { return raw_io_event_buffer; }

const CommandBuffer &getCommandBuffer() { return commandBuffer; }
} // namespace oriongl::core
