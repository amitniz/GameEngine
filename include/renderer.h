#pragma once

#include "shader.h"
#include "mesh.h"

class Renderer{
public:
  Renderer() = delete;
  static void draw(Mesh& mesh,ShaderProgram& shader_program);
  static inline void clear() {glClear(GL_COLOR_BUFFER_BIT);}
};
