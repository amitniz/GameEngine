#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "include/mesh.h"
#include "include/window.h"
#include "include/shader.h"
#include "include/renderer.h"
#include "include/logging.h"

float vertices[] = {
  -1, -1, 0,
   1, -1, 0,
   0,  1, 0,
   0,  0, 1.5,
};

unsigned int indices[] = {
  0, 1, 2,
  0, 1, 3,
  1, 2, 3,
  0, 2, 3,
};


int main() {
    LOG_DEBUG("start engine");
    Window * main_window = new Window(1280,1280);
    main_window->init();

    VertexShader* vs = new VertexShader();
    vs->from_file("shaders/shader.vert");
    FragmentShader* fs = new FragmentShader();
    fs->from_file("shaders/shader.frag");

    ShaderProgram* program = new ShaderProgram();
    program->add_shader(vs);
    program->add_shader(fs);
    Mesh* mesh = new Mesh();
    mesh->create(vertices,indices,sizeof(vertices),sizeof(indices));
  
    float angle = 0.0f;
    float inc = 1;

    while (!main_window->should_close())
    {
      Renderer::clear();
      Renderer::draw(*mesh,*program);
      /* Swap front and back buffers */
      if( angle >= 360) angle = 0;
      angle+=inc;
      program->set_perspective(45.0f,main_window->get_ratio(),0.1f,100.0f);
      program
        ->reset_model()
        ->translate(0.0f,0.0f,-7.5f)
        ->rotate(angle,glm::vec3(1.0f,1.0f,0.4f))
        ->scale(2,2,2);
      ;

      main_window->swap_buffers();
      /* Poll for and process events */
      glfwPollEvents();
    }
  
  // clean up
  delete vs;
  delete fs;
  delete program;
  delete mesh;
  LOG_DEBUG("quiting");
  return 0;
}
