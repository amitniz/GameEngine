#include "include/mesh.h"
#include "include/logging.h"

Mesh::Mesh() {
  m_vbo = 0;
  m_ibo = 0;
  m_vao = 0;
  m_idx_count = 0;
}

Mesh *Mesh::create(GLfloat *vertices, unsigned *indices, unsigned n_vertices,
                   unsigned n_indices) {

  this->m_idx_count = n_indices;

  // vao
  GLCALL(glGenVertexArrays(1, &this->m_vao));
  GLCALL(glBindVertexArray(this->m_vao));
  // ibo
  GLCALL(glGenBuffers(1, &this->m_ibo));
  GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ibo));
  GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * n_indices,
                      indices, GL_STATIC_DRAW));
  // vbo
  GLCALL(glGenBuffers(1, &this->m_vbo));
  GLCALL(glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo));
  GLCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * n_vertices,
                      vertices, GL_STATIC_DRAW));

  // positions attribute
  GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                               sizeof(vertices[0]) * 8, 0));
  GLCALL(glEnableVertexAttribArray(0));
  // Textures attribute
  GLCALL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
                               sizeof(vertices[0]) * 8,
                               (void *)(sizeof(vertices[0]) * 3)));
  GLCALL(glEnableVertexAttribArray(1));
  // normals attribute
  GLCALL(glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE,
                               sizeof(vertices[0]) * 8,
                               (void *)(sizeof(vertices[0]) * 5)));
  GLCALL(glEnableVertexAttribArray(2));

  // unbinds
  GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));         // unbind vbo
  GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); // unbind ibo

  GLCALL(glBindVertexArray(0)); // unbind vao

  return this;
}

void Mesh::clear() {

  if (!this->m_ibo) {
    GLCALL(glDeleteBuffers(1, &this->m_ibo));
    this->m_ibo = 0;
  }
  if (!this->m_vbo) {
    GLCALL(glDeleteBuffers(1, &this->m_vbo));
    this->m_vbo = 0;
  }
  if (!this->m_vao) {
    GLCALL(glDeleteVertexArrays(1, &this->m_vao));
    this->m_vao = 0;
  }
  this->m_idx_count = 0;
}

void Mesh::render() {
  // bind vao
  GLCALL(glBindVertexArray(this->m_vao));
  // bind ibo
  GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ibo));
  // draw mesh
  GLCALL(glDrawElements(GL_TRIANGLES, this->m_idx_count, GL_UNSIGNED_INT, 0));
  // unbind ibo
  GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
  // unbind vao
  GLCALL(glBindVertexArray(0));
}

Mesh::~Mesh() { this->clear(); }
