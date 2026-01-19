#include <Shader.h>
#include <glad.h>
#include <gtest/gtest.h>

namespace oriongl::graphics {

const char *vertex_shader = R"(#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 nPos;
layout (location = 2) in vec2 aTextCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec3 NormalPos;
out vec2 TextCoord;

void main()
{
  gl_Position = projection * view * model * vec4(aPos, 1.0);
  FragPos = vec3(model * vec4(aPos, 1.0));
  NormalPos = mat3(transpose(inverse(model))) * nPos;
  TextCoord = aTextCoord;
})";

TEST(ShaderTest, create_one_shader) {
    Shader shader_stage{ShaderType::VERTEX, vertex_shader, {}};

    EXPECT_NE(shader_stage.getId(), 0);
    EXPECT_TRUE(glIsShader(shader_stage.getId()));
};

TEST(ShaderTest, create_multiple_shaders) {
    Shader shader_arr[] = {
        {ShaderType::VERTEX, vertex_shader, {}},
        {ShaderType::VERTEX, vertex_shader, {}},
        {ShaderType::VERTEX, vertex_shader, {}},
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

} // namespace oriongl::graphics
