#include <Mesh.h>
#include <glad.h>
#include <gtest/gtest.h>

namespace oriongl::graphics {

vertex_array vertexes = {-0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 0.5f, 0.0f};

indexes_array indexes = {0, 1, 2};

TEST(MeshTest, create_a_mesh) {
    Mesh mesh{vertexes, indexes};
    EXPECT_NE(mesh.getVAO(), 0);
    EXPECT_TRUE(glIsVertexArray(mesh.getVAO()));
}

TEST(MeshTest, create_multiple_meshes) {
    Mesh mesh_arr[] = {
        {vertexes, indexes},
        {vertexes, indexes},
        {vertexes, indexes},
    };

    for (size_t it = 0; it < 3; it++) {
        EXPECT_NE(mesh_arr[it].getVAO(), 0);
        EXPECT_TRUE(glIsVertexArray(mesh_arr[it].getVAO()));
    }

    for (size_t i = 0; i < 2; i++) {
        for (size_t j = i + 1; j < 3; j++) {
            EXPECT_NE(mesh_arr[i].getVAO(), mesh_arr[j].getVAO());
        }
    }
} // namespace oriongl::graphics

TEST(MeshTest, correct_index_size) {
    Mesh mesh{vertexes, indexes};
    EXPECT_EQ(mesh.getIndexSize(), 3);
}

} // namespace oriongl::graphics
