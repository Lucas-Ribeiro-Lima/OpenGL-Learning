#pragma once

#include <Camera.h>
#include <InputLayer.h>
#include <InputSystemForward.h>
#include <array>

namespace oriongl::core {

class InputSystem {
    std::array<input::KeyState, MAX_KEY_BUFFER_SIZE> key_states;

    void updateKeyState();
    void updateCommandBuffer();

  public:
    InputSystem();
    void process();
    void cleanup();
};
} // namespace oriongl::core
