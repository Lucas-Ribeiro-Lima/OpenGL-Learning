#include <InputSystem.h>

namespace {
using Key = oriongl::core::input::Key;
using KeyState = oriongl::core::input::KeyState;
using Command = oriongl::core::Command;
using Target = oriongl::core::Target;
using Action = oriongl::core::Action;

oriongl::core::InputContext ctx;

struct CommandHelper {
    Key key;
    KeyState state;
    Command action;
};

CommandHelper command_helper[] = {
    {Key::Escape, KeyState::Pressed, {Target::EngineTarget, Action::Quit}},
    {Key::W, KeyState::Pressed, {Target::CameraTarget, Action::MoveForward}},
    {Key::S, KeyState::Pressed, {Target::CameraTarget, Action::MoveBackward}},
    {Key::A, KeyState::Pressed, {Target::CameraTarget, Action::MoveLeftward}},
    {Key::D, KeyState::Pressed, {Target::CameraTarget, Action::MoveRightward}},
    {Key::Space, KeyState::Pressed, {Target::CameraTarget, Action::MoveUpward}},
    {Key::Ctrl, KeyState::Pressed, {Target::CameraTarget, Action::MoveDownward}},
};

} // namespace

namespace oriongl::core {
InputSystem::InputSystem() { key_states.fill(KeyState::Released); };

void InputSystem::process() {
    updateKeyState();
    updateCommandBuffer();
}

void InputSystem::cleanup() { ctx.commands.clear(); }

void InputSystem::updateCommandBuffer() {
    for (auto &helper : command_helper) {
        if (key_states[helper.key] == helper.state)
            ctx.commands.push_back(helper.action);
    };
}

void InputSystem::updateKeyState() {
    for (auto &event : ctx.events) {
        if (event.type == EventType::Keyboard) {
            Key key = input::KeyTranslationLayer::getKey(event.data[0]);
            KeyState state = input::KeyTranslationLayer::getState(event.data[1]);

            key_states[key] = state;
        }
    }

    ctx.events.clear();
}

const CommandBuffer &getCommands() { return ctx.commands; };
EventBuffer &getEvents() { return ctx.events; };

} // namespace oriongl::core
