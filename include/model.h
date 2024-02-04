#pragma once

#include "material.h"
#include "mesh.h"
#include "shader.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/ext/vector_float3.hpp>
#include <string>
#include <vector>

class Model {
public:
  Model() = default;
  ~Model();
  Model *load(const std::string &file_path);
  void render();
  void clear();

  Model *reset();
  Model *translate(float x, float y, float z);
  Model *scale(float x, float y, float z);
  Model *rotate(float degree, glm::vec3 rotation_axis);
  ShaderProgram *get_shader(){return m_materials[0] ? m_materials[0]->get_shader_program(): nullptr;}
private:
  void load_mesh(aiMesh *mesh);
  void load_nodes(aiNode *node, const aiScene *scene);
  void load_materials(const aiScene *scene);

  std::vector<Mesh *> m_meshes;
  std::vector<Material *> m_materials;
  std::vector<unsigned> m_mesh_2_tex;
};
