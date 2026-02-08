#include <Engine.h>
#include <string>
#include <vector>

const char vertex_shader[] = {
#embed "assets/vertex_shader.glsl"
    , '\0'};

const char frag_shader[] = {
#embed "assets/frag_shader.glsl"
    , '\0'};

const char frag_light_shader[] = {
#embed "assets/frag_light_shader.glsl"
    , '\0'};

// clang-format off
const std::vector<glm::vec3> cube_positions = {
    {  35.0f,   0.0f,   0.0f },
    {  24.7f,   8.0f,  24.7f },
    {   0.0f,  15.0f,  35.0f },
    { -24.7f,   8.0f,  24.7f },
    { -35.0f,   0.0f,   0.0f },

    { -24.7f,  -8.0f, -24.7f },
    {   0.0f, -15.0f, -35.0f },
    {  24.7f,  -8.0f, -24.7f },

    {  17.5f,  20.0f,  30.3f },
    { -17.5f, -20.0f, -30.3f }
};

const std::vector<glm::vec3> light_positions = {
  { 0.0f, 0.0f, 0.0f },
};
// clang-format on

std::vector<std::string> box_material{
    "assets/container.png",
    "assets/container_specular.png",
    "assets/black_pixel.png",
};

int main() {
    oriongl::Engine engine;
    oriongl::core::ResourceSystem resource_system;

    auto cube_mesh = resource_system.createCubeMesh(3.0f);
    auto cube_program = resource_system.createShader(vertex_shader, frag_shader, {});
    auto cube_material = resource_system.createMaterial(box_material);
    auto cube_model = resource_system.createModel("CUBE_MODEL_1", cube_program, cube_mesh, cube_material);

    oriongl::core::Entity cube_ent;
    cube_ent.model = cube_model;
    cube_ent.instances = cube_positions;

    auto light_program = resource_system.createShader(vertex_shader, frag_light_shader, {});
    auto sphere_mesh = resource_system.createSphereMesh(5.0f);
    auto sphere_model = resource_system.createModel("SPHERE_MODEL_1", light_program, sphere_mesh);

    oriongl::core::Entity sphere_ent;
    sphere_ent.model = sphere_model;
    sphere_ent.instances = light_positions;

    oriongl::core::Scene scene;
    scene.entities.insert(scene.entities.end(), {cube_ent, sphere_ent});
    scene.lights.directional = {0.0f, -0.45f, -0.45f};

    engine.setScene(scene);
    engine.run();
    return 0;
}
