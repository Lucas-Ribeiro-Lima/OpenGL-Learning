#include <InputSystem.h>

namespace {
using Key = oriongl::core::Key;
using KeyState = oriongl::core::KeyState;
using Command = oriongl::core::Command;
using Action = oriongl::core::Action;

oriongl::core::InputContext ctx;

struct CommandHelper {
    Key key;
    KeyState state;
    Command action;
};

CommandHelper command_helper[] = {
    {Key::Escape, KeyState::Pressed, {Action::Quit}},       {Key::W, KeyState::Pressed, {Action::MoveForward}},
    {Key::S, KeyState::Pressed, {Action::MoveBackward}},    {Key::A, KeyState::Pressed, {Action::MoveLeftward}},
    {Key::D, KeyState::Pressed, {Action::MoveRightward}},   {Key::Space, KeyState::Pressed, {Action::MoveUpward}},
    {Key::Ctrl, KeyState::Pressed, {Action::MoveDownward}},
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
            Key key = KeyTranslationLayer::getKey(event.first);
            KeyState state = KeyTranslationLayer::getState(event.second);
            key_states[key] = state;
        } else {
            ctx.commands.push_back({Action::LookAt, {(float)event.first, (float)event.second}});
        }
    }

    ctx.events.clear();
}

const CommandBuffer &getCommands() { return ctx.commands; };
EventBuffer &getEvents() { return ctx.events; };

} // namespace oriongl::core
