#include "include/renderer.h"
#include "include/logging.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace Odyssey;
float Renderer::last_draw_time;

void Renderer::draw(Mesh &mesh, ShaderProgram &shader_program) {
  shader_program.use();
  mesh.render();
}

void Renderer::draw(Model &model, ShaderProgram &shader_program) {
  shader_program.use();
  model.render();
}

void Renderer::draw(Scene &scene) {
  float now = glfwGetTime();
  if (!last_draw_time)
    last_draw_time = now;
  scene.render(now - last_draw_time);
  last_draw_time = now;
}

OpenGLBuffersIDs::OpenGLBuffersIDs(unsigned vao, unsigned ibo, unsigned vbo)
    : vao(vao), ibo(ibo), vbo(vbo) {}

OpenGLBuffersIDs Renderer::createMesh(float *vertices, unsigned *indices,
                                      unsigned n_vertices, unsigned n_indices) {
  unsigned vao, vbo, ibo;

  // vao
  GLCALL(glGenVertexArrays(1, &vao));
  GLCALL(glBindVertexArray(vao));
  // ibo
  GLCALL(glGenBuffers(1, &ibo));
  GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
  GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * n_indices,
                      indices, GL_STATIC_DRAW));
  // vbo
  GLCALL(glGenBuffers(1, &vbo));
  GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
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

  return OpenGLBuffersIDs(vao, ibo, vbo);
}

void Renderer::createShadowMap(unsigned int width, unsigned int height,
                               unsigned *fbo, unsigned *shadow_map_id) {
  GLCALL(glGenFramebuffers(1, fbo));

  GLCALL(glGenTextures(1, shadow_map_id));
  GLCALL(glBindTexture(GL_TEXTURE_2D, *shadow_map_id));
  GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0,
                      GL_DEPTH_COMPONENT, GL_FLOAT, nullptr));
  GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
  GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
  GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

  GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, *fbo));
  GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                                GL_TEXTURE_2D, *shadow_map_id, 0));

  GLCALL(glDrawBuffer(GL_NONE));
  GLCALL(glReadBuffer(GL_NONE));

  GLenum err = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if (err != GL_FRAMEBUFFER_COMPLETE) {
    LOG_CRITICAL("%s has failed to create a framebuffer. error code: %i",
                 __func__, err);
  }

  GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void Renderer::writeShadowMap(unsigned fbo) {
  GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, fbo));
}

void Renderer::readShadowMap(unsigned texture_unit, unsigned shadow_map_id){
  GLCALL(glActiveTexture(texture_unit));
  GLCALL(glBindTexture(GL_TEXTURE_2D, shadow_map_id ));
}

void Renderer::deleteShadowMap(unsigned int fbo, unsigned int shadow_map_id){
  if(fbo) GLCALL(glDeleteFramebuffers(1, &fbo));
  if(shadow_map_id) GLCALL(glDeleteTextures(1, &shadow_map_id));
}
