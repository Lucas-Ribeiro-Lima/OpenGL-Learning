#include <GLFW/glfw3.h>
#include <InputLayer.h>
#include <array>

#define MAX_KEY_BUFFER_SIZE 516

namespace {

using Key = oriongl::core::input::Key;
constexpr auto key_buffer_lut = [] {
    std::array<Key, MAX_KEY_BUFFER_SIZE> lut{};
    lut.fill(Key::UnKnown);

    lut[GLFW_KEY_W] = Key::W;
    lut[GLFW_KEY_A] = Key::A;
    lut[GLFW_KEY_S] = Key::S;
    lut[GLFW_KEY_D] = Key::D;
    lut[GLFW_KEY_LEFT_CONTROL] = Key::Ctrl;
    lut[GLFW_KEY_SPACE] = Key::Space;
    lut[GLFW_KEY_ESCAPE] = Key::Escape;

    return lut;
}();

} // namespace

namespace oriongl::core::input {

Key KeyTranslationLayer::getKey(int keyCode) {
    if (keyCode < 0 || keyCode > MAX_KEY_BUFFER_SIZE)
        return Key::UnKnown;
    return key_buffer_lut[keyCode];
}

} // namespace oriongl::core::input
