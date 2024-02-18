#pragma once

#include <GL/glew.h>
#include <vector>

class Mesh {

public:
  Mesh();
  Mesh *create(float *verticies, unsigned *indices, unsigned n_verticies,
               unsigned n_indices);

  inline Mesh *create(std::vector<float> &verticies,
                      std::vector<unsigned> &indicies) {
    return create(verticies.data(), indicies.data(), verticies.size(),
                  indicies.size());
  }

  ~Mesh();
  void render();


private:
  void clear();
  GLuint m_vao, m_vbo, m_ibo;
  GLsizei m_idx_count;
};
