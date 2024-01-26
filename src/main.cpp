#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "include/mesh.h"
#include "include/window.h"
#include "include/shader.h"
#include "include/renderer.h"
static unsigned int compile_shader(const std::string &source, GLenum type) {
  GLuint shader = glCreateShader(type);
  const char *src = source.c_str();
  glShaderSource(shader, 1, &src, nullptr);
  glCompileShader(shader);

  return shader;
}

static unsigned int create_shader(const std::string &vertex_shader,
                                  const std::string &fragment_shader) {
  GLuint program = glCreateProgram();
  GLuint vs = compile_shader(vertex_shader, GL_VERTEX_SHADER);
  GLuint fs = compile_shader(fragment_shader, GL_FRAGMENT_SHADER);

  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glValidateProgram(program);

  glDeleteShader(vs);
  glDeleteShader(fs);
  return program;
}

float vertices[] = {
  -0.5f,-0.5f,0.0f,
  0.5f,-0.5f,0.0f,
  0.0f,0.5f,0.0f,
};

unsigned int indices[] = {
  0,1,2
};


int main() {

    Window * main_window = new Window();
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
     
    while (!main_window->should_close())
    {
        Renderer::clear();
        Renderer::draw(*mesh,*program);
        /* Swap front and back buffers */
        main_window->swap_buffers();

        /* Poll for and process events */
        glfwPollEvents();
    }

  delete vs;
  delete fs;
  delete program;
  delete mesh;
  return 0;
}
