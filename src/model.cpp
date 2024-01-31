
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

  load_nodes(scene->mRootNode, scene);
  load_materials(scene);
  return this;
}

void Model::load_nodes(aiNode *node, const aiScene *scene) {
  for (int i = 0; i < node->mNumMeshes; i++) {
    load_mesh(scene->mMeshes[node->mMeshes[i]]);
  }

  for (int i = 0; i < node->mNumChildren; i++) {
    load_nodes(node->mChildren[i], scene);
  }
}
void Model::load_mesh(aiMesh *mesh) {
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

void Model::load_materials(const aiScene *scene) {
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

        if (!m_materials[i]->load_texture()) {
          delete m_materials[i];
          m_materials[i] = nullptr;
        }
      }
    }
    if (m_materials[i] == nullptr){
            m_materials[i] = new Material();
            m_materials[i]->load_texture();
    }
  }
}

void Model::render() {
  for (int i = 0; i < m_meshes.size();i++){
        unsigned texture_idx = m_mesh_2_tex[i];
        if(texture_idx < m_materials.size() && m_materials[texture_idx]){
            m_materials[texture_idx]->use();
        }
        m_meshes[i]->render();
    }

}

void Model::clear() {
  for (Mesh *mesh : m_meshes)
    mesh->clear();
}

Model::~Model() {
  clear();
  for (Mesh *mesh : m_meshes)
    delete mesh;
}
