#include <Shader.h>
#include <glad.h>
#include <gtest/gtest.h>

namespace oriongl::graphics {

const char vertex_src[] = {
#embed "assets/valid_vertex_src.glsl"
    , '\0'};

const char fragment_src[] = {
#embed "assets/valid_fragment_src.glsl"
    , '\0'};

// Shader missing the version line
const char invalid_vertex_src[] = {
#embed "assets/invalid_vertex_src.glsl"
    , '\0'};

TEST(ShaderTest, vertex_create_one_shader) {
    Shader vertex_stage{ShaderType::VERTEX, vertex_src, {}};
    Shader fragment_stage{ShaderType::FRAGMENT, fragment_src, {}};

    EXPECT_NE(vertex_stage.getId(), 0);
    EXPECT_TRUE(glIsShader(vertex_stage.getId()));

    EXPECT_NE(fragment_stage.getId(), 0);
    EXPECT_TRUE(glIsShader(fragment_stage.getId()));
};

TEST(ShaderTest, vertex_create_multiple_shaders) {
    Shader shader_arr[] = {
        {ShaderType::VERTEX, vertex_src, {}},
        {ShaderType::VERTEX, vertex_src, {}},
        {ShaderType::VERTEX, vertex_src, {}},
    };

    for (size_t it = 0; it < 3; it++) {
        EXPECT_NE(shader_arr[it].getId(), 0);
        EXPECT_TRUE(glIsVertexArray(shader_arr[it].getId()));
    }

    for (size_t i = 0; i < 2; i++) {
        for (size_t j = i + 1; j < 3; j++) {
            EXPECT_NE(shader_arr[i].getId(), shader_arr[j].getId());
        }
    }
};

TEST(ShaderTest, defines_injection) {
    Shader shader_stage{ShaderType::VERTEX, vertex_src, {"USE_EMISSION_TEXTURE"}};
    std::string src_with_defines = shader_stage.getSource();

    size_t second_line = std::string{vertex_src}.find("\n") + 1;
    size_t define_position = src_with_defines.find(std::string{"#define USE_EMISSION_TEXTURE"});

    EXPECT_EQ(define_position, second_line);
};

TEST(ShaderTest, invalid_shader_must_throw) {
    try {
        Shader invalid_shader{ShaderType::VERTEX, invalid_vertex_src};
        FAIL();
    } catch (std::runtime_error &e) {
    }
}

} // namespace oriongl::graphics
