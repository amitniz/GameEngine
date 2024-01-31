#pragma once

#include "material.h"
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
  void load_nodes(aiNode* node, const aiScene *scene); 
void load_materials(const aiScene* scene); 
  std::vector<Mesh*> m_meshes;
    std::vector<Material*> m_materials; 
    std::vector<unsigned> m_mesh_2_tex;
};
