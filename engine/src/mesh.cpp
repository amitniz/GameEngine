#include "include/mesh.h"
#include "include/logging.h"
#include "include/renderer.h"

using namespace Odyssey;

Mesh::Mesh() {
  m_vbo = 0;
  m_ibo = 0;
  m_vao = 0;
  m_idx_count = 0;
}

Mesh *Mesh::create(GLfloat *vertices, unsigned *indices, unsigned n_vertices,
                   unsigned n_indices) {

  m_idx_count = n_indices;
  
  OpenGLBuffersIDs mesh_ids = Renderer::createMesh(vertices, indices, n_vertices, n_indices);
  m_vao = mesh_ids.vao;
  m_vbo = mesh_ids.vbo;
  m_ibo = mesh_ids.ibo;

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
