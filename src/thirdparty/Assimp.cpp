#include <ModelLoader.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <assert.h>
#include <span>
#include <string>

namespace oriongl::core {

class ModelLoaderImpl {
    ModelData data;
    const aiScene *scene = nullptr;

  public:
    ModelLoaderImpl() {};
    ModelData process(const aiScene *sc);
    void processNode(aiNode *node);
    void processMesh(unsigned int meshId);
    void processMaterial(unsigned int materialId);
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

    MeshData mesh_data;

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
        vertexes.push_back(ai_text_coords[i]->x);
        vertexes.push_back(ai_text_coords[i]->y);
    }

    data.mesh_data.push_back(std::make_tuple(vertexes, indexes));
    processMaterial(mesh->mMaterialIndex);
};

void ModelLoaderImpl::processMaterial(unsigned int materialId) {
    aiMaterial *material = scene->mMaterials[materialId];
    unsigned int diffuse_cnt = material->GetTextureCount(aiTextureType_DIFFUSE);
    unsigned int specular_cnt = material->GetTextureCount(aiTextureType_SPECULAR);
    unsigned int emissive_cnt = material->GetTextureCount(aiTextureType_EMISSIVE);

    aiString diffuse_path{};
    if (diffuse_cnt)
        material->GetTexture(aiTextureType_DIFFUSE, 0, &diffuse_path);

    aiString emissive_path{};
    if (specular_cnt)
        material->GetTexture(aiTextureType_EMISSIVE, 0, &emissive_path);

    aiString specular_path{};
    if (emissive_cnt)
        material->GetTexture(aiTextureType_SPECULAR, 0, &specular_path);

    data.material_data.push_back(
        std::vector{std::string{diffuse_path.data}, std::string{specular_path.data}, std::string{emissive_path.data}});
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
    const aiScene *scene = importer.ReadFile(src, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::string error_msg{importer.GetErrorString()};
        throw std::runtime_error("ERROR::ASSIMP::" + error_msg);
    }

    ModelLoaderImpl model_impl;
    return model_impl.process(scene);
};

} // namespace oriongl::core
