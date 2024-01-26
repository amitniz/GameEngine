#include "include/mesh.h"

Mesh::Mesh() {
  m_vbo = 0;
  m_ibo = 0;
  m_vao = 0;
  m_idx_count = 0;
}

Mesh* Mesh::create(GLfloat *vertices, unsigned *indices,
                         unsigned n_vertices, unsigned n_indices) {

  this->m_idx_count = n_indices;

  // vao
  glGenVertexArrays(1, &this->m_vao);
  glBindVertexArray(this->m_vao);
  // ibo
  glGenBuffers(1, &this->m_ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * n_indices, indices,
               GL_STATIC_DRAW);
  // vbo
  glGenBuffers(1, &this->m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * n_vertices,
               vertices, GL_STATIC_DRAW);

  // attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  //unbinds
  glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind vbo
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //unbind ibo

  glBindVertexArray(0); // unbind vao

  return this;
}


void Mesh::clear(){

  if(!this->m_ibo){
    glDeleteBuffers(1,&this->m_ibo);
    this->m_ibo = 0;
  }
  if(!this->m_vbo){
    glDeleteBuffers(1,&this->m_vbo);
    this->m_vbo = 0;
  }
  if(!this->m_vao){
    glDeleteVertexArrays(1,&this->m_vao);
    this->m_vao = 0;
  }
  this->m_idx_count = 0;
}

void Mesh::render(){
  //bind vao
  glBindVertexArray(this->m_vao);
  //bind ibo
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,this->m_ibo);
  //draw mesh
  glDrawElements(GL_TRIANGLES,this->m_idx_count,GL_UNSIGNED_INT,0);
  //unbind ibo
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
  //unbind vao
  glBindVertexArray(0);
  
}

Mesh::~Mesh(){
  this->clear();
}
