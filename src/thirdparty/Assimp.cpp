#include <ModelLoader.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <assert.h>
#include <filesystem>
#include <span>
#include <string>

namespace oriongl::core {

class ModelLoaderImpl {
    ModelData data;
    const aiScene *scene = nullptr;
    const std::filesystem::path model_root_path;

  public:
    ModelLoaderImpl(std::string model_path) : model_root_path(std::filesystem::path(model_path).parent_path()) {};
    ModelData process(const aiScene *sc);
    void processNode(aiNode *node);
    void processMesh(unsigned int meshId);
    void processMaterial(unsigned int materialId);
    std::string normalizeTexturePath(aiString texture_path);
};

ModelData ModelLoaderImpl::process(const aiScene *sc) {
    assert(sc != nullptr && "Scene file cant be null");
    scene = sc;

    processNode(scene->mRootNode);
    return data;
};

void ModelLoaderImpl::processMesh(unsigned int meshId) {
    aiMesh *mesh = scene->mMeshes[meshId];
    aiVector3D *ai_vertexes = mesh->mVertices;
    aiVector3D *ai_normals = mesh->mNormals;
    aiVector3D **ai_text_coords = mesh->mTextureCoords;

    graphics::vertex_array vertexes;
    std::span index_span(mesh->mFaces->mIndices, mesh->mFaces->mNumIndices);
    graphics::indexes_array indexes(index_span.begin(), index_span.end());

    for (size_t i = 0; i < mesh->mNumVertices; i++) {
        vertexes.push_back(ai_vertexes[i].x);
        vertexes.push_back(ai_vertexes[i].y);
        vertexes.push_back(ai_vertexes[i].z);
        vertexes.push_back(ai_normals[i].x);
        vertexes.push_back(ai_normals[i].y);
        vertexes.push_back(ai_normals[i].z);
        vertexes.push_back(ai_text_coords[0][i].x);
        vertexes.push_back(ai_text_coords[0][i].y);
    }

    data.mesh_data.push_back(std::make_tuple(vertexes, indexes));
    processMaterial(mesh->mMaterialIndex);
};

void ModelLoaderImpl::processMaterial(unsigned int materialId) {
    aiMaterial *material = scene->mMaterials[materialId];
    unsigned int diffuse_cnt = material->GetTextureCount(aiTextureType_DIFFUSE);
    unsigned int specular_cnt = material->GetTextureCount(aiTextureType_SPECULAR);
    unsigned int emissive_cnt = material->GetTextureCount(aiTextureType_EMISSIVE);

    aiString ai_diffuse_path;
    if (diffuse_cnt)
        material->GetTexture(aiTextureType_DIFFUSE, 0, &ai_diffuse_path);
    auto normalized_diffuse_path = normalizeTexturePath(ai_diffuse_path);

    aiString ai_specular_path;
    if (emissive_cnt)
        material->GetTexture(aiTextureType_SPECULAR, 0, &ai_specular_path);
    auto normalized_specular_path = normalizeTexturePath(ai_specular_path);

    aiString ai_emissive_path;
    if (specular_cnt)
        material->GetTexture(aiTextureType_EMISSIVE, 0, &ai_emissive_path);
    auto normalized_emissive_path = normalizeTexturePath(ai_emissive_path);

    data.material_data.push_back(std::vector{normalized_diffuse_path, normalized_specular_path, normalized_emissive_path});
};

std::string ModelLoaderImpl::normalizeTexturePath(aiString texture_path) {
    if (texture_path.Empty())
        return "assets/black_pixel.png";

    return model_root_path / texture_path.data;
};

void ModelLoaderImpl::processNode(aiNode *node) {
    for (size_t it = 0; it < node->mNumMeshes; it++) {
        processMesh(node->mMeshes[it]);
    }

    for (size_t it = 0; it < node->mNumChildren; it++) {
        processNode(node->mChildren[it]);
    }
};

ModelData ModelLoader::loadFromFile(std::string src) {
    Assimp::Importer importer;

    const aiScene *scene = importer.ReadFile(src, aiProcess_Triangulate);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::string error_msg{importer.GetErrorString()};
        throw std::runtime_error("ERROR::ASSIMP::" + error_msg);
    }

    ModelLoaderImpl model_impl{src};
    return model_impl.process(scene);
};

} // namespace oriongl::core
