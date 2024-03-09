#pragma once

#include "game_object.h"
#include "material.h"
#include "mesh.h"
#include "shader.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <glm/ext/vector_float3.hpp>
#include <string>
#include <vector>
#include "logging.h"

namespace Odyssey{

class Model: public GameObject{
public:
    Model() = default;
    ~Model();
    Model *load(const std::string &file_path);
    static Model *loadFromJson(const std::string &json_string);

    Model *translate(float x, float y, float z);
    Model *translate(glm::vec3 xyz);

    Model *scale(float x, float y, float z);
    Model *scale(glm::vec3 xyz);

    Model *rotate(glm::vec3 axis, float angle);

    inline const glm::mat4& getModel() const {
        TODO("make sure the matrix is init by default to ones matrix");
        return m_model_matrix;
    };

private:
    void loadMesh(aiMesh *mesh);
    void loadNodes(aiNode *node, const aiScene *scene);
    void loadMaterials(const aiScene *scene);

    std::vector<Mesh *> m_meshes;
    std::vector<Material *> m_materials;
    std::vector<unsigned> m_mesh_2_tex;
    glm::mat4 m_model_matrix;

    friend class Renderer;
};
};
