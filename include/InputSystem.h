#pragma once

#include <Camera.h>
#include <InputSystemForward.h>

namespace oriongl::core {
class InputSystem {
  public:
    InputSystem();
    void process();
    void cleanup();
};
} // namespace oriongl::core
