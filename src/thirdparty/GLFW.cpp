#include <GLFW/glfw3.h>
#include <InputLayer.h>
#include <array>

namespace {

using Key = oriongl::core::input::Key;
using KeyState = oriongl::core::input::KeyState;

constexpr auto key_buffer_lut = [] {
    std::array<Key, MAX_KEY_BUFFER_SIZE> lut{};
    lut.fill(Key::Unknown);

    lut[GLFW_KEY_W] = Key::W;
    lut[GLFW_KEY_A] = Key::A;
    lut[GLFW_KEY_S] = Key::S;
    lut[GLFW_KEY_D] = Key::D;
    lut[GLFW_KEY_LEFT_CONTROL] = Key::Ctrl;
    lut[GLFW_KEY_SPACE] = Key::Space;
    lut[GLFW_KEY_ESCAPE] = Key::Escape;

    return lut;
}();

constexpr auto state_buffer_lut = [] {
    std::array<KeyState, 4> lut{};

    lut[GLFW_RELEASE] = KeyState::Released;
    lut[GLFW_PRESS] = KeyState::Pressed;
    lut[GLFW_REPEAT] = KeyState::Repeat;

    return lut;
}();
} // namespace

namespace oriongl::core::input {

Key KeyTranslationLayer::getKey(int key_code) {
    if (key_code > 0 || key_code < MAX_KEY_BUFFER_SIZE)
        return key_buffer_lut[key_code];
}

KeyState KeyTranslationLayer::getState(int state_code) { return state_buffer_lut[state_code]; }
} // namespace oriongl::core::input
