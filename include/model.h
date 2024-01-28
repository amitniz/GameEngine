#pragma once

#include "mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <string>
#include <vector>

class Model {
public:
  Model() = default;
  ~Model();
  Model *load(const std::string &file_path);
  void render();
  void clear();

private:
  void load_mesh(aiMesh *mesh);
  void load_node(aiNode* node, const aiScene *scene);
  std::vector<Mesh *> m_meshes;
};
