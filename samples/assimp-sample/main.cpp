#include <Engine.h>
#include <ResourceSystem.h>

const char vertex_shader[] = {
#embed "assets/vertex_shader.glsl"
    , '\0'};

const char frag_shader[] = {
#embed "assets/frag_shader.glsl"
    , '\0'};

const char *backpack_src = "assets/survival_guitar_backpack/scene.gltf";

int main() {
    oriongl::Engine engine;
    oriongl::core::ResourceSystem resource_system;

    auto program = resource_system.createShader(vertex_shader, frag_shader, {});
    auto backpack = resource_system.createModel("SURVIVEL_BACKPACK", program, backpack_src);

    engine.loadEntityToScene(backpack, std::vector<glm::vec3>{{0.0f, 0.0f, 5.0f}});

    engine.run();
    return 0;
};
