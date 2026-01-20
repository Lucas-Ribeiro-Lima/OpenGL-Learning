#include <ResourceSystem.h>
#include <gtest/gtest.h>

namespace oriongl::core {

const char vertex_src[] = {
#embed "assets/valid_vertex_src.glsl"
    , '\0'};

const char fragment_src[] = {
#embed "assets/valid_fragment_src.glsl"
    , '\0'};

const char fragment_light_src[] = {
#embed "assets/frag_light_shader.glsl"
    , '\0'};

class ResourceSystemTest : public testing::Test {
  protected:
    static std::shared_ptr<ResourceSystem> resource_system;
    void SetUp() override { resource_system = std::make_shared<ResourceSystem>(); };

    void TearDown() override { resource_system = nullptr; };
};

std::shared_ptr<ResourceSystem> ResourceSystemTest::resource_system = nullptr;

TEST_F(ResourceSystemTest, must_return_cached_shader) {
    auto shader_1 = resource_system->createShaderStage(graphics::ShaderType::VERTEX, vertex_src, {"USE_FEATURE_X"});
    auto shader_2 = resource_system->createShaderStage(graphics::ShaderType::VERTEX, vertex_src, {"USE_FEATURE_X"});

    EXPECT_EQ(shader_1, shader_2);
}

TEST_F(ResourceSystemTest, must_return_different_shaders_objects) {
    auto shader_1 = resource_system->createShaderStage(graphics::ShaderType::VERTEX, vertex_src, {});
    auto shader_2 = resource_system->createShaderStage(graphics::ShaderType::VERTEX, vertex_src, {"USE_FEATURE_X"});

    EXPECT_NE(shader_1, shader_2);
}

TEST_F(ResourceSystemTest, must_return_cached_meshes) {
    auto cube_1 = resource_system->createCubeMesh(5.0f);
    auto cube_2 = resource_system->createCubeMesh(5.0f);

    auto sphere_1 = resource_system->createSphereMesh(3.0f);
    auto sphere_2 = resource_system->createSphereMesh(3.0f);

    // clang-format off
    graphics::vertex_array triangle_vertexes{
    //  x     y    z   n_x  n_y, n_z  t_x, t_y
      -5.0, -5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
       5.0, -5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
       0.0,  5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    };

    graphics::indexes_array triangle_indexes{
      0, 1, 2
    };
    // clang-format on

    auto triangle_1 = resource_system->createMesh("TRIANGLE", triangle_vertexes, triangle_indexes);
    auto triangle_2 = resource_system->createMesh("TRIANGLE", triangle_vertexes, triangle_indexes);

    EXPECT_EQ(cube_1, cube_2);
    EXPECT_EQ(sphere_1, sphere_2);
    EXPECT_EQ(triangle_1, triangle_2);
}

TEST_F(ResourceSystemTest, must_return_different_mesh_objects) {
    auto cube_1 = resource_system->createCubeMesh(5.0f);
    auto cube_2 = resource_system->createCubeMesh(3.0f);

    auto sphere_1 = resource_system->createSphereMesh(3.0f);
    auto sphere_2 = resource_system->createSphereMesh(5.0f);

    // clang-format off
    graphics::vertex_array triangle_vertexes{
    //  x     y    z   n_x  n_y, n_z  t_x, t_y
      -5.0, -5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
       5.0, -5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
       0.0,  5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    };

    graphics::indexes_array triangle_indexes{
      0, 1, 2
    };
    // clang-format on

    auto triangle_1 = resource_system->createMesh("TRIANGLE_1", triangle_vertexes, triangle_indexes);
    auto triangle_2 = resource_system->createMesh("TRIANGLE_2", triangle_vertexes, triangle_indexes);

    EXPECT_NE(cube_1, cube_2);
    EXPECT_NE(sphere_1, sphere_2);
    EXPECT_NE(triangle_1, triangle_2);
}

TEST_F(ResourceSystemTest, must_return_cached_program) {
    auto program_1 = resource_system->createShader(vertex_src, fragment_src, {});
    auto program_2 = resource_system->createShader(vertex_src, fragment_src, {});

    EXPECT_EQ(program_1, program_2);
}

TEST_F(ResourceSystemTest, must_return_different_program_objects) {
    auto program_1 = resource_system->createShader(vertex_src, fragment_src, {"FEATURE_X"});
    auto program_2 = resource_system->createShader(vertex_src, fragment_src, {});
    auto program_3 = resource_system->createShader(vertex_src, fragment_light_src, {});

    EXPECT_NE(program_1, program_2);
    EXPECT_NE(program_1, program_3);
    EXPECT_NE(program_2, program_3);
}

} // namespace oriongl::core
