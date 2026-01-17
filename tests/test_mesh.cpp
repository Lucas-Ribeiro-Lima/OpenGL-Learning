#include <Mesh.h>
#include <glad.h>
#include <gtest/gtest.h>

namespace oriongl::graphics {

vertex_array vertexes = {-0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 0.5f, 0.0f};

indexes_array indexes = {0, 1, 2};

TEST(MeshTest, create_a_mesh) {
    Mesh mesh{vertexes, indexes};
    EXPECT_NE(mesh.getVAO(), 0);
}

TEST(MeshTest, create_multiple_meshes) {
    Mesh mesh1{vertexes, indexes};
    Mesh mesh2{vertexes, indexes};
    Mesh mesh3{vertexes, indexes};

    EXPECT_NE(mesh1.getVAO(), 0);
    EXPECT_NE(mesh2.getVAO(), 0);
    EXPECT_NE(mesh3.getVAO(), 0);
}

TEST(MeshTest, correct_index_size) {
    Mesh mesh{vertexes, indexes};
    EXPECT_EQ(mesh.getIndexSize(), 3);
}

TEST(MeshTest, is_a_vertex_array_buffer_) {
    Mesh mesh{vertexes, indexes};

    EXPECT_TRUE(glIsVertexArray(mesh.getVAO()));
}

} // namespace oriongl::graphics
