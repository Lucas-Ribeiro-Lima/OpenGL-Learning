#include <Engine.h>
#include <ResourceSystem.h>

const char vertex_shader[] = {
#embed "assets/vertex_shader.glsl"
    , '\0'};

const char frag_shader[] = {
#embed "assets/frag_shader.glsl"
    , '\0'};

const char *backpack_src = "assets/survival_guitar_backpack/scene.gltf";
const char *dark_knight_src = "assets/dark_knight/scene.gltf";
const char *sea_keep_src = "assets/sea_keep/scene.gltf";

int main() {
    oriongl::Engine engine;
    oriongl::core::ResourceSystem resource_system;

    auto program = resource_system.createShader(vertex_shader, frag_shader);

    // auto knight = resource_system.createModel("dark_knight", program, dark_knight_src);
    // engine.loadEntityToScene(knight, std::vector<glm::vec3>{{0.0f, 100.0f, 150.0f}});

    // auto backpack = resource_system.createModel("backpack", program, backpack_src);
    // engine.loadEntityToScene(backpack, std::vector<glm::vec3>{{0.0f, 0.0f, -500.0f}});

    auto sea_keep = resource_system.createModel("SEA_KEEP", program, sea_keep_src);
    engine.loadEntityToScene(sea_keep, std::vector<glm::vec3>{{0.0f, -300.0f, -500.0f}});

    engine.run();
    return 0;
}
