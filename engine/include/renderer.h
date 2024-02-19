/*/
* This code contains an abstraction layer to the OpenGL API used for rendering objects.
* In the future I might add support for other graphic frameworks.
*/
#pragma once

#include "shader.h"
#include "mesh.h"
#include "model.h"
#include "logging.h"
#include "scene.h"
#include <GL/gl.h>

namespace Odyssey{
struct OpenGLBuffersIDs{
  OpenGLBuffersIDs(unsigned vao,unsigned ibo,unsigned vbo);
  unsigned vao;
  unsigned ibo;
  unsigned vbo;
};


class Renderer{
  static float last_draw_time;
public:
  Renderer() = delete;
  static void draw(Mesh& mesh,ShaderProgram& shader_program);
  static void draw(Model& model,ShaderProgram& shader_program);
  static void draw(Scene& scene);
  static OpenGLBuffersIDs createMesh(float *vertices, unsigned *indices, unsigned n_vertices,unsigned n_indices);

  static void createShadowMap(unsigned width, unsigned height, unsigned *fbo, unsigned *shadow_map_id);
  static void writeShadowMap(unsigned fbo);
  static void readShadowMap(unsigned texture_unit, unsigned shadow_map_id);
  static void deleteShadowMap(unsigned fbo, unsigned shadow_map_id);

  static inline void clearScreen() {GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));}
};
};
