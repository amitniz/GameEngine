
#include "include/model.h"
#include "include/logging.h"

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
    for (int i=0; i< scene->mNumMeshes;i++){
        this->load_mesh(scene->mMeshes[i]);
    }
  return this;
}

void Model::load_mesh(aiMesh *mesh) {
  std::vector<float> vertices;
  std::vector<unsigned> indices;
  for (int i = 0; i < mesh->mNumVertices; i++) {
    vertices.insert(vertices.end(), {mesh->mVertices[i].x, mesh->mVertices[i].y,
                                     mesh->mVertices[i].z});
  }
  for (int i = 0; i < mesh->mNumFaces; i++) {
    aiFace face = mesh->mFaces[i];
    for (int j = 0; j < face.mNumIndices; j++) {
      indices.push_back(face.mIndices[j]);
    }
  }

    Mesh* n_mesh = new Mesh();
    n_mesh->create(vertices,indices);
    this->m_meshes.push_back(n_mesh);
}

void Model::render(){
    for (Mesh* mesh :m_meshes) mesh->render();
}

void Model::clear(){
    for (Mesh* mesh: m_meshes) mesh->clear();
}

Model::~Model(){
    this->clear();
    for (Mesh *mesh: m_meshes) delete mesh;
}
