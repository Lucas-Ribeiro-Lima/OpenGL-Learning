#include <Engine.h>
#include <ResourceSystem.h>
#include <Scene.h>

const char vertex_shader[] = {
#embed "../../src/assets/vertex_shader.glsl"
    , '\0'};

const char frag_shader[] = {
#embed "../../src/assets/frag_shader.glsl"
    , '\0'};

const char *backpack_src = "assets/survival_guitar_backpack/scene.gltf";
const char *dark_knight_src = "assets/dark_knight/scene.gltf";
const char *sea_keep_src = "assets/sea_keep/scene.gltf";

int main() {
    oriongl::Engine engine;
    oriongl::core::ResourceSystem resource_system;

    auto program = resource_system.createShader(vertex_shader, frag_shader);

    auto sea_keep = resource_system.createModel("SEA_KEEP", program, sea_keep_src);
    oriongl::core::Entity sea_keep_ent;
    sea_keep_ent.model = sea_keep;
    sea_keep_ent.instances.push_back({0.0f, -300.0f, -500.0f});

    std::vector<oriongl::graphics::PointLight> point_light_positions = {
        {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.4f}, {1.0f, 0.0f, 0.0f}},
    };

    oriongl::core::Lighting scene_lighting{point_light_positions};

    oriongl::core::Scene scene{.lights = scene_lighting};
    scene.entities.push_back(sea_keep_ent);

    scene.camera = {45.0f, oriongl::ratio::FullHD, 0.1f, 3000.0f};

    engine.setScene(scene);
    engine.run();

    return 0;
}
