#pragma once

#include <cstdint>


namespace oriongl::core::input {

enum Key : uint8_t {
    UnKnown,
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

class KeyTranslationLayer {
public:
  static Key getKey(int keyCode);
};
} // namespace oriongl::core::input
