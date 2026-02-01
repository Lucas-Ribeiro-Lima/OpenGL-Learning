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
    const std::string model_path;
    std::filesystem::path model_root_path;

  public:
    ModelLoaderImpl(std::string model_path) : model_path(model_path) {
        model_root_path = std::filesystem::path(model_path).parent_path();
    };
    ModelData process();
    void processNode(aiNode *node);
    void processMesh(unsigned int meshId);
    graphics::vertex_array processVertex(aiMesh *mesh);
    graphics::indexes_array processIndexes(aiMesh *mesh);
    MaterialData processMaterial(unsigned int materialId);
    inline std::string getRelativeModelTexturePath(aiString texture_path);
};

ModelData ModelLoaderImpl::process() {
    Assimp::Importer importer;

    scene = importer.ReadFile(model_path, aiProcess_Triangulate | aiProcess_PreTransformVertices);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::string error_msg{importer.GetErrorString()};
        throw std::runtime_error("ERROR::ASSIMP::" + error_msg);
    }

    processNode(scene->mRootNode);
    return data;
};

void ModelLoaderImpl::processNode(aiNode *node) {
    for (size_t it = 0; it < node->mNumMeshes; it++) {
        processMesh(node->mMeshes[it]);
    }

    for (size_t it = 0; it < node->mNumChildren; it++) {
        processNode(node->mChildren[it]);
    }
};

void ModelLoaderImpl::processMesh(unsigned int meshId) {
    aiMesh *mesh = scene->mMeshes[meshId];

    auto vertexes = processVertex(mesh);
    auto indexes = processIndexes(mesh);
    auto material = processMaterial(mesh->mMaterialIndex);

    data.mesh_data.push_back(std::make_tuple(vertexes, indexes));
    data.material_data.push_back(material);
};

graphics::vertex_array ModelLoaderImpl::processVertex(aiMesh *mesh) {
    graphics::vertex_array vertexes;

    bool hasNormals = mesh->HasNormals();
    bool hasTextCoords = mesh->HasTextureCoords(0);

    for (size_t i = 0; i < mesh->mNumVertices; i++) {
        aiVector3D &ai_vertexes = mesh->mVertices[i];
        aiVector3D &ai_normals = mesh->mNormals[i];
        aiVector3D &ai_text_coords = mesh->mTextureCoords[0][i];

        vertexes.insert(vertexes.end(), {ai_vertexes.x, ai_vertexes.y, ai_vertexes.z});

        if (hasNormals)
            vertexes.insert(vertexes.end(), {ai_normals.x, ai_normals.y, ai_normals.z});
        else
            vertexes.insert(vertexes.end(), 3, 0.0f);

        if (hasTextCoords)
            vertexes.insert(vertexes.end(), {ai_text_coords.x, ai_text_coords.y});
        else
            vertexes.insert(vertexes.end(), 2, 0.0f);
    }

    return vertexes;
}

graphics::indexes_array ModelLoaderImpl::processIndexes(aiMesh *mesh) {
    graphics::indexes_array indexes;

    for (size_t i = 0; i < mesh->mNumFaces; i++) {
        aiFace &face = mesh->mFaces[i];
        auto indexes_span = std::span(face.mIndices, face.mNumIndices);
        indexes.insert(indexes.end(), indexes_span.begin(), indexes_span.end());
    }

    return indexes;
}

MaterialData ModelLoaderImpl::processMaterial(unsigned int materialId) {
    std::vector<std::string> textures;

    aiMaterial *material = scene->mMaterials[materialId];
    unsigned int diffuse_cnt = material->GetTextureCount(aiTextureType_DIFFUSE);
    unsigned int specular_cnt = material->GetTextureCount(aiTextureType_SPECULAR);
    unsigned int emissive_cnt = material->GetTextureCount(aiTextureType_EMISSIVE);

    if (diffuse_cnt) {
        aiString path;
        material->GetTexture(aiTextureType_DIFFUSE, 0, &path);
        if (!path.Empty())
            textures.push_back(getRelativeModelTexturePath(path));
    }

    if (specular_cnt) {
        aiString path;
        material->GetTexture(aiTextureType_SPECULAR, 0, &path);
        if (!path.Empty())
            textures.push_back(getRelativeModelTexturePath(path));
    }

    if (emissive_cnt) {
        aiString path;
        material->GetTexture(aiTextureType_EMISSIVE, 0, &path);
        if (!path.Empty())
            textures.push_back(getRelativeModelTexturePath(path));
    }

    return textures;
};

inline std::string ModelLoaderImpl::getRelativeModelTexturePath(aiString texture_path) {
    return model_root_path / texture_path.data;
};

ModelData ModelLoader::loadFromFile(std::string src) {
    ModelLoaderImpl model_impl{src};
    return model_impl.process();
};

} // namespace oriongl::core
