#pragma once

#include "shader.h"
#include "mesh.h"
#include "logging.h"
#include <GL/gl.h>
class Renderer{
public:
  Renderer() = delete;
  static void draw(Mesh& mesh,ShaderProgram& shader_program);
  static inline void clear() {GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));}
};
