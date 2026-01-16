#pragma once

#include <cstdint>
#include <vector>
#define MAX_KEY_BUFFER_SIZE 516

namespace oriongl::core {

enum Key : uint16_t {
    Unknown,
    // Moment
    W,
    A,
    S,
    D,

    // Modifiers
    Ctrl,
    Alt,
    Space,
    Escape,
};

enum KeyState : uint8_t {
    Pressed,
    Released,
    Repeat,
};

class KeyTranslationLayer {
  public:
    static Key getKey(int key_code);
    static KeyState getState(int state_code);
};

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
