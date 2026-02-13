#pragma once

#include <Camera.h>
#include <Entity.h>
#include <Light.h>

namespace oriongl::core {

struct Scene {
    std::vector<Entity> entities;
    core::Lighting lights;
    Camera camera;
};

} // namespace oriongl::core
