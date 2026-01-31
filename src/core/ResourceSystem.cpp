#include <ModelLoader.h>
#include <ResourceSystem.h>

#include <assert.h>

namespace oriongl::core {

std::shared_ptr<graphics::Program> ResourceSystem::createShader(std::string vertex_src, std::string frag_src,
                                                                std::vector<std::string> defines) {
    auto vertex_shader = createShaderStage(graphics::ShaderType::VERTEX, vertex_src, defines);
    auto fragment_shader = createShaderStage(graphics::ShaderType::FRAGMENT, frag_src, defines);

    auto key = program_manager.concatenateHashKeys(vertex_src, frag_src, defines);
    return program_manager.createResource(key, std::move(vertex_shader), std::move(fragment_shader));
};

std::shared_ptr<graphics::Shader> ResourceSystem::createShaderStage(graphics::ShaderType type, std::string src,
                                                                    std::vector<std::string> defines) {
    return shader_manager.createResource(type, src, defines);
};

std::shared_ptr<graphics::Texture> ResourceSystem::createTexture(std::string src) {
    return texture_manager.createResource(src);
};

std::shared_ptr<graphics::Material> ResourceSystem::createMaterial(std::vector<std::string> textures) {
    auto material = std::make_shared<graphics::Material>();

    for (auto &path : textures) {
        auto texture = createTexture(path);
        material->loadTexture(texture);
    }

    return material;
};

std::shared_ptr<graphics::Mesh> ResourceSystem::createCubeMesh(float side_size) {
    auto cube_data = generateCubeMeshData(side_size);
    auto key = std::string("CUBE_MESH_KEY") + std::to_string(side_size);

    return mesh_manager.createResource(key, cube_data.first, cube_data.second);
};

std::shared_ptr<graphics::Mesh> ResourceSystem::createSphereMesh(float radius) {
    auto sphere_data = generateSphereMeshData(radius);
    auto key = std::string("SPHERE_MESH_KEY") + std::to_string(radius);

    return mesh_manager.createResource(key, sphere_data.first, sphere_data.second);
}

std::shared_ptr<graphics::Mesh> ResourceSystem::createMesh(std::string key, graphics::vertex_array vertexes,
                                                           graphics::indexes_array indexes) {
    return mesh_manager.createResource(key, vertexes, indexes);
}

std::shared_ptr<graphics::Model> ResourceSystem::createModel(std::string model_id,
                                                             std::shared_ptr<graphics::Program> program,
                                                             std::shared_ptr<graphics::Mesh> mesh,
                                                             std::shared_ptr<graphics::Material> material) {
    auto model = model_manager.createResource(model_id, program);
    model->loadData(mesh, material);

    return model;
}

std::shared_ptr<graphics::Model> ResourceSystem::createModel(std::string model_id,
                                                             std::shared_ptr<graphics::Program> program, std::string src) {
    auto model = model_manager.createResource(model_id, program);

    auto [mesh_data, material_data] = ModelLoader::loadFromFile(src);

    assert(mesh_data.size() == material_data.size() && "Mesh and Materials must be the same size");
    for (size_t it = 0; it < mesh_data.size(); it++) {
        auto mesh = createMesh(model_id + std::to_string(it), std::get<0>(mesh_data[it]), std::get<1>(mesh_data[it]));
        auto material = createMaterial(material_data[it]);

        model->loadData(mesh, material);
    }

    return model;
};

std::pair<graphics::vertex_array, graphics::indexes_array> ResourceSystem::generateCubeMeshData(float side_size) {
    // clang-format off
    static graphics::vertex_array vertexesCube = {
        // ===== Front (+Z)
        -side_size, -side_size,  side_size,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
         side_size, -side_size,  side_size,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
         side_size,  side_size,  side_size,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
        -side_size,  side_size,  side_size,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,

        // ===== Back (-Z)
         side_size, -side_size, -side_size,   0.0f, 0.0f,-1.0f,   0.0f, 0.0f,
        -side_size, -side_size, -side_size,   0.0f, 0.0f,-1.0f,   1.0f, 0.0f,
        -side_size,  side_size, -side_size,   0.0f, 0.0f,-1.0f,   1.0f, 1.0f,
         side_size,  side_size, -side_size,   0.0f, 0.0f,-1.0f,   0.0f, 1.0f,

        // ===== Left (-X)
        -side_size, -side_size, -side_size,  -1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
        -side_size, -side_size,  side_size,  -1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
        -side_size,  side_size,  side_size,  -1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
        -side_size,  side_size, -side_size,  -1.0f, 0.0f, 0.0f,   0.0f, 1.0f,

        // ===== Right (+X)
         side_size, -side_size,  side_size,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
         side_size, -side_size, -side_size,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
         side_size,  side_size, -side_size,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
         side_size,  side_size,  side_size,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f,

        // ===== Top (+Y)
        -side_size,  side_size,  side_size,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
         side_size,  side_size,  side_size,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
         side_size,  side_size, -side_size,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
        -side_size,  side_size, -side_size,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,

        // ===== Bottom (-Y)
        -side_size, -side_size, -side_size,   0.0f,-1.0f, 0.0f,   0.0f, 0.0f,
         side_size, -side_size, -side_size,   0.0f,-1.0f, 0.0f,   1.0f, 0.0f,
         side_size, -side_size,  side_size,   0.0f,-1.0f, 0.0f,   1.0f, 1.0f,
        -side_size, -side_size,  side_size,   0.0f,-1.0f, 0.0f,   0.0f, 1.0f
    };

    static graphics::indexes_array indexesCube = {
        0,  1,  2,  0,  2,  3,  // Front
        4,  5,  6,  4,  6,  7,  // Back
        8,  9,  10, 8,  10, 11, // Left
        12, 13, 14, 12, 14, 15, // Right
        16, 17, 18, 16, 18, 19, // Top
        20, 21, 22, 20, 22, 23  // Bottom
    };
    // clang-format on

    return std::make_pair(vertexesCube, indexesCube);
}

constexpr std::pair<graphics::vertex_array, graphics::indexes_array> ResourceSystem::generateSphereMeshData(float radius) {
    std::vector<float> vertexesSphere;
    std::vector<unsigned int> indexesSphere;

    int stacks = 40;   // latitude
    int slices = 1600; // longitude

    for (int i = 0; i <= stacks; ++i) {
        float phi = (static_cast<float>(i) / stacks) * M_PI;
        float y = cosf(phi) * radius;
        float r = sinf(phi) * radius;

        for (int j = 0; j <= slices; ++j) {
            float theta = (static_cast<float>(j) / slices) * 2.0f * M_PI;
            float x = r * cosf(theta);
            float z = r * sinf(theta);

            // posicao
            vertexesSphere.push_back(x);
            vertexesSphere.push_back(y);
            vertexesSphere.push_back(z);

            // normal (apontando para fora)
            vertexesSphere.push_back(x);
            vertexesSphere.push_back(y);
            vertexesSphere.push_back(z);

            // coordenadas de textura
            vertexesSphere.push_back(1.0f - (static_cast<float>(j) / slices));
            vertexesSphere.push_back(1.0f - (static_cast<float>(i) / stacks));
        }
    }

    // Indices
    for (int i = 0; i < stacks; ++i) {
        for (int j = 0; j < slices; ++j) {
            int first = (i * (slices + 1)) + j;
            int second = first + slices + 1;

            indexesSphere.push_back(first);
            indexesSphere.push_back(second);
            indexesSphere.push_back(first + 1);

            indexesSphere.push_back(second);
            indexesSphere.push_back(second + 1);
            indexesSphere.push_back(first + 1);
        }
    }

    return std::pair{vertexesSphere, indexesSphere};
}
} // namespace oriongl::core
