#include <Program.h>
#include <Shader.h>
#include <glad.h>
#include <gtest/gtest.h>
#include <memory.h>

namespace oriongl::graphics {

const char vertex_src[] = {
#embed "assets/valid_vertex_src.glsl"
    , '\0'};

const char fragment_src[] = {
#embed "assets/valid_fragment_src.glsl"
    , '\0'};

class ProgramTest : public testing::Test {
  protected:
    static std::shared_ptr<Shader> vertex_shader;
    static std::shared_ptr<Shader> fragment_shader;

    void SetUp() override {
        vertex_shader = std::make_shared<Shader>(ShaderType::VERTEX, vertex_src);
        fragment_shader = std::make_shared<Shader>(ShaderType::FRAGMENT, fragment_src);
    };

    void TearDown() override {
        vertex_shader = nullptr;
        fragment_shader = nullptr;
    };
};

std::shared_ptr<Shader> ProgramTest::vertex_shader = nullptr;
std::shared_ptr<Shader> ProgramTest::fragment_shader = nullptr;

TEST_F(ProgramTest, create_and_link) {
    Program program{vertex_shader, fragment_shader};
    EXPECT_NE(program.getId(), 0);
    EXPECT_TRUE(glIsProgram(program.getId()));
};

// TEST_F(ProgramTest, wrong_type_shaders_must_throw_on_linkage) {
//     EXPECT_ANY_THROW(({ Program program{wrong_type_vertex_shader, wrong_type_fragment_shader}; }));
// }

} // namespace oriongl::graphics
