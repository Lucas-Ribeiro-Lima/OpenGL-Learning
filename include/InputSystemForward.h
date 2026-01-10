#pragma once

#include <vector>

namespace oriongl::core {

enum EventType { Mouse, Keyboard };

typedef double EventData[2];

struct Event {
    EventType type;
    EventData data;
};

typedef std::vector<Event> EventBuffer;

enum Action : uint8_t {
    MoveForward,
    MoveBackward,
    MoveLeftward,
    MoveRightward,
    MoveUpward,
    ModeDownward,

    Quit,
};

enum Target : uint8_t { CameraTarget, ActorTarget, EngineTarget };

struct Command {
    Target target;
    Action action;
    float value;
};

typedef std::vector<Command> CommandBuffer;

const CommandBuffer &getCommandBuffer();

} // namespace oriongl::core
