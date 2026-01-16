#include <Engine.h>
#include <ResourceManagers.h>
#include <string>
#include <vector>

const char vertex_shader[] = {
#embed "assets/vertex_shader.glsl"
};

const char frag_shader[] = {
#embed "assets/frag_shader.glsl"
};

const char frag_light_shader[] = {
#embed "assets/frag_light_shader.glsl"
};

int main() {
    oriongl::Engine engine;
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
    // clang-format on

    std::vector<std::string> box_material{
        "assets/container.png",
        "assets/container_specular.png",
        "assets/black_pixel.png",
    };

    auto cube_mesh = oriongl::core::storage::MeshLoaderHelper::getCubeMesh(3.0f);
    auto cube_shader = oriongl::core::storage::ShaderManager::getProgram(vertex_shader, frag_shader);
    auto cube_model = oriongl::core::storage::ModelManager::getModel(cube_shader, cube_mesh, box_material);

    auto sphere_mesh = oriongl::core::storage::MeshLoaderHelper::getSphereMesh(5.0f);
    auto light_shader = oriongl::core::storage::ShaderManager::getProgram(vertex_shader, frag_light_shader);
    auto light_model = oriongl::core::storage::ModelManager::getModel(light_shader, sphere_mesh, {});

    engine.loadEntityToScene(cube_model, cube_positions);
    engine.loadEntityToScene(light_model, {glm::vec3(0.0f)});

    engine.run();

    return 0;
}
