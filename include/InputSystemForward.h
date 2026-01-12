#pragma once

#include <vector>

namespace oriongl::core {

enum EventType { Mouse, Keyboard };

struct Event {
    EventType type;
    double first;
    double second;
};

typedef std::vector<Event> EventBuffer;

enum Action : uint8_t {
    MoveForward,
    MoveBackward,
    MoveLeftward,
    MoveRightward,
    MoveUpward,
    MoveDownward,
    
    LookAt,

    Quit,
};

struct Command {
    Action action;
    double value[2];
};

typedef std::vector<Command> CommandBuffer;
typedef CommandBuffer DeferredBuffer;

struct InputContext {
    EventBuffer events;
    CommandBuffer commands;
    DeferredBuffer deferred;
};

const CommandBuffer &getCommands();
EventBuffer &getEvents();

} // namespace oriongl::core
