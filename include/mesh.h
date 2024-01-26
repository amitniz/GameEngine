#pragma once 

#include <GL/glew.h>

class Mesh{

public:
  Mesh();
  Mesh* create(GLfloat *verticies, unsigned *indices, unsigned n_verticies, unsigned n_indices);
  void render();
  void clear();
 
  ~Mesh();

private:
  GLuint m_vao,m_vbo,m_ibo;
  GLsizei m_idx_count; 
};
