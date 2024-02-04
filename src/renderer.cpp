#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "include/renderer.h"

float Renderer::last_draw_time;

void Renderer::draw(Mesh& mesh, ShaderProgram& shader_program){
  shader_program.use();
  mesh.render();
}

void Renderer::draw(Model& model,ShaderProgram& shader_program){
    shader_program.use();
    model.render();
}

void Renderer::draw(Scene& scene){
  float now = glfwGetTime();
  if (!last_draw_time) last_draw_time = now;
  scene.render(now - last_draw_time);
  last_draw_time = now;
}
