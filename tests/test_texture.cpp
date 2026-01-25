#include <Texture.h>
#include <glad.h>
#include <gtest/gtest.h>
#include <test_resources.h>

namespace oriongl::graphics {

TEST(TextureTest, create_and_initializate) {
    Texture tex{DUMMY_TEXTURE_PATH};

    EXPECT_NE(tex.getTex(), 0);
    EXPECT_TRUE(glIsTexture(tex.getTex()));
};

TEST(TextureTest, create_and_initializate_multiple) {
    Texture array[] = {{DUMMY_TEXTURE_PATH}, {DUMMY_TEXTURE_PATH}, {DUMMY_TEXTURE_PATH}};

    for (auto &tex : array) {
        EXPECT_TRUE(glIsTexture(tex.getTex()));
    }

    for (size_t i = 0; i < 2; i++) {
        for (size_t j = i + 1; j < 3; j++) {
            EXPECT_NE(array[i].getTex(), array[j].getTex());
        }
    }
}

TEST(TextureTest, inexistent_texture_file_must_throw) {
    EXPECT_ANY_THROW(({ Texture tex{"Inexistent_texture_path"}; }));
}

} // namespace oriongl::graphics
