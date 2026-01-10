#pragma once

#include <Camera.h>
#include <InputSystemForward.h>

namespace oriongl::core {
class InputSystem {
    EventBuffer raw_io_event_buffer;

  public:
    InputSystem();
    void processCamera(Camera &camera);
    EventBuffer &getIoEventBufferQueue();
};
} // namespace oriongl::core
