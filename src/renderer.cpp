#include <GL/glew.h>
#include "include/renderer.h"

void Renderer::draw(Mesh& mesh, ShaderProgram& shader_program){
  shader_program.use();
  mesh.render();
}

void Renderer::draw(Model& model,ShaderProgram& shader_program){
    shader_program.use();
    model.render();
}
