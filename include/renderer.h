#pragma once

#include "shader.h"
#include "mesh.h"
#include "model.h"
#include "logging.h"
#include "scene.h"
#include <GL/gl.h>


class Renderer{
  static float last_draw_time;
public:
  Renderer() = delete;
  static void draw(Mesh& mesh,ShaderProgram& shader_program);
  static void draw(Model& model,ShaderProgram& shader_program);
  static void draw(Scene& scene);
  static inline void clear() {GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));}
};
