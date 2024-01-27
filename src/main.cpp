#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "include/mesh.h"
#include "include/window.h"
#include "include/shader.h"
#include "include/renderer.h"
#include "include/logging.h"

float vertices[] = {
  -0.5f,-0.5f,0.0f,
  0.5f,-0.5f,0.0f,
  0.0f,0.5f,0.0f,
};

unsigned int indices[] = {
  0,1,2
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
  
    float move_x = 0.2f;
    float inc = 0.01;

    while (!main_window->should_close())
    {
      Renderer::clear();
      Renderer::draw(*mesh,*program);
      /* Swap front and back buffers */
      if(move_x >=0.8 || move_x <= -0.8) inc = -inc;
      move_x += inc;
      program
        ->reset_model()
        ->translate(move_x,move_x, 0.0f)
        ->scale(0.5f,0.5f,0.0f);

      main_window->swap_buffers();
      /* Poll for and process events */
      glfwPollEvents();
    }
  
  // clean up
  delete vs;
  delete fs;
  delete program;
  delete mesh;
  LOG_DEBUG("quiting..");
  return 0;
}
