#include "include/model.h"
#include "include/logging.h"
#include <assimp/material.h>
#include <assimp/types.h>
#include <glm/gtc/type_ptr.hpp>
#include "nlohmann/json.hpp"

using namespace Odyssey;

#define TO_RADIANS(x) (float)(x * 3.14159265f / 180.0)

Model *Model::loadFromJson(const std::string &json_string) {
    TODO("errors check");
    nlohmann::json j = nlohmann::json::parse(json_string);
    std:: string path = j["path"];
    Model* model = (new Model())->load(path);
    if(!j["position"].is_null()){
        float x = j["position"]["x"];
        float y = j["position"]["y"];
        float z = j["position"]["z"];
        model->translate(x,y,z);
    }
    if(!j["scale"].is_null()){
        float x = j["scale"]["x"];
        float y = j["scale"]["y"];
        float z = j["scale"]["z"];
        model->scale(x,y,z);
    }
    TODO("add rotate");
    return model;
}

Model *Model::load(const std::string &file_path) {
    Assimp::Importer importer;
    const aiScene *scene =
        importer.ReadFile(file_path, aiProcess_Triangulate | aiProcess_FlipUVs |
                          aiProcess_GenSmoothNormals |
                          aiProcess_JoinIdenticalVertices);

    if (!scene) {
        LOG_ERROR("Model (%s) failed to load: %s", file_path.c_str(),
                  importer.GetErrorString());
        return this;
    }

    loadNodes(scene->mRootNode, scene);
    loadMaterials(scene);
    return this;
}


Model* Model::rotate(glm::vec3 axis, float degree){
    this->m_model_matrix = glm::rotate(this->m_model_matrix, TO_RADIANS(degree), axis);
    return this;
}


Model* Model::scale(float x, float y, float z){
    return scale(glm::vec3(x,y,z));
}

Model* Model::scale(glm::vec3 xyz){
    this->m_model_matrix = glm::scale(this->m_model_matrix, xyz);
    return this;
}

Model* Model::translate(float x, float y, float z){
    return translate(glm::vec3(x,y,z));
}
Model* Model::translate(glm::vec3 xyz){
    this->m_model_matrix = glm::translate(this->m_model_matrix, xyz);
    return this;
}

void Model::loadNodes(aiNode *node, const aiScene *scene) {
    for (int i = 0; i < node->mNumMeshes; i++) {
        loadMesh(scene->mMeshes[node->mMeshes[i]]);
    }

    for (int i = 0; i < node->mNumChildren; i++) {
        loadNodes(node->mChildren[i], scene);
    }
}
void Model::loadMesh(aiMesh *mesh) {
    std::vector<float> vertices;
    std::vector<unsigned> indices;
    for (int i = 0; i < mesh->mNumVertices; i++) {
        vertices.insert(vertices.end(), {mesh->mVertices[i].x, mesh->mVertices[i].y,
            mesh->mVertices[i].z});

        if (mesh->mTextureCoords[0]) {
            vertices.insert(vertices.end(), {mesh->mTextureCoords[0][i].x,
                mesh->mTextureCoords[0][i].y});
            // textures UVs
        } else {
            vertices.insert(vertices.end(), {0.0f, 0.0f});
        }
        // normals
        vertices.insert(vertices.end(), {mesh->mNormals[i].x, mesh->mNormals[i].y,
            mesh->mNormals[i].z});
    }

    for (int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    Mesh *n_mesh = new Mesh();
    n_mesh->create(vertices, indices);
    this->m_meshes.push_back(n_mesh);
    this->m_mesh_2_tex.push_back(mesh->mMaterialIndex);
}

void Model::loadMaterials(const aiScene *scene) {
    m_materials.resize(scene->mNumMaterials);
    for (int i = 0; i < scene->mNumMaterials; i++) {
        aiMaterial *material = scene->mMaterials[i];
        m_materials[i] = nullptr;

        if (material->GetTextureCount(aiTextureType_DIFFUSE)) {
            aiString path;
            if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {
                int idx = std::string(path.data).rfind("\\");
                std::string filename = std::string(path.data).substr(idx + 1);

                std::string texture_path = std::string("assets/textures/") + filename;

                m_materials[i] = (new Material())->addTexture(texture_path);
            }
        }
    }
}

Model::~Model() {
    for (Mesh *mesh : m_meshes)
    delete mesh;
    for (Material* material: m_materials)
    delete material;
}

