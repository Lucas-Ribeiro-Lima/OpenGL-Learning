#pragma once

#include <cstdint>
#define MAX_KEY_BUFFER_SIZE 516

namespace oriongl::core::input {

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

enum KeyState: uint8_t {
  Pressed,
  Released,
  Repeat,
};

class KeyTranslationLayer {
  public:
    static Key getKey(int key_code);
    static KeyState getState(int state_code);
};
} // namespace oriongl::core::input
