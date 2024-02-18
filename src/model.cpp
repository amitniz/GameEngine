
#include "include/model.h"
#include "include/logging.h"
#include <assimp/material.h>
#include <assimp/types.h>

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

Model* Model::setTexture(Texture* texture){
  if (m_materials[0]){
    m_materials[0]->setTexture(texture);
  }
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

        std::string texPath = std::string("assets/textures/") + filename;

        m_materials[i] = new Material(texPath.c_str());

        if (!m_materials[i]->loadTexture()) {
          delete m_materials[i];
          m_materials[i] = nullptr;
        }
      }
    }
    if (m_materials[i] == nullptr) {
      m_materials[i] = new Material();
      m_materials[i]->loadTexture();
    }
  }
}

void Model::render() {
  // if(m_materials[0]) m_materials[0]->use_shader();
  for (int i = 0; i < m_meshes.size(); i++) {
    unsigned texture_idx = m_mesh_2_tex[i];
    if (texture_idx < m_materials.size() && m_materials[texture_idx]) {
      m_materials[texture_idx]->useTexture();
    }
    m_meshes[i]->render();
  }
}

Model::~Model() {
  for (Mesh *mesh : m_meshes)
    delete mesh;
  for (Material* material: m_materials)
    delete material;
}

Model* Model::reset(){
  if(this->m_materials[0])
    this->m_materials[0]->getShaderProgram()->resetModel();
  return this;
}
Model *Model::translate(float x, float y, float z) {
  if (this->m_materials[0])
    this->m_materials[0]->getShaderProgram()->translate(x, y, z);
  return this;
}

Model *Model::scale(float x, float y, float z) {
  if (this->m_materials[0])
    this->m_materials[0]->getShaderProgram()->scale(x, y, z);
  return this;
}
Model *Model::rotate(float degree, glm::vec3 rotation_axis) {
  if (this->m_materials[0])
    this->m_materials[0]->getShaderProgram()->rotate(degree, rotation_axis);
  return this;
}
