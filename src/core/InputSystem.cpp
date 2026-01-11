#include <InputLayer.h>
#include <InputSystem.h>

namespace {
oriongl::core::InputContext ctx;
}

namespace oriongl::core {
InputSystem::InputSystem() {};

void InputSystem::process() {
    for (auto &event : ctx.events) {
        if (input::KeyTranslationLayer::getKey(event.data[0]) == input::Key::Escape)
            ctx.commands.push_back(Command{Target::EngineTarget, Action::Quit});
    }

    ctx.events.clear();
}

void InputSystem::cleanup() { ctx.commands.clear(); }

const CommandBuffer &getCommands() { return ctx.commands; };
EventBuffer &getEvents() { return ctx.events; };

} // namespace oriongl::core
