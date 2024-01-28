#include "include/camera.h"
#include "include/logging.h"
#include "include/mesh.h"
#include "include/model.h"
#include "include/renderer.h"
#include "include/shader.h"
#include "include/texture.h"
#include "include/window.h"
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>

float vertices[] = {
//   x  y   z  u  v
    -1, 0, -1, 0, 0, // bottom left - 0
    1,  0, -1, 0.3333, 0, // bottom right - 1
    -1, 0, 1,  1, 0, // upper left   - 2
    1,  0, 1,  0.6666, 0, // upper right   - 3
    0,  2, 0,  0.5,1, // top          - 4
};

unsigned int indices[] = {
    0, 1, 2,
    1, 2, 3,
    0, 1, 4,
    2, 3, 4,
    0, 2, 4,
    1, 3, 4,
};

int main() {
  LOG_DEBUG("starting the engine..");
  // create window
  Window *main_window = new Window(1200, 1200);
  main_window->init();

  // create Mesh
  Mesh *mesh = new Mesh();
  mesh->create(vertices, indices, sizeof(vertices), sizeof(indices));
  // create texture
  Texture *brick_texture = new Texture("assets/textures/red_brick.png");
  brick_texture->load();

  // create model
  // Model *model = new Model();
  // model->load("models/space_shuttle.stl");
  // create shaders and shaderProgram
  VertexShader *vs = new VertexShader();
  vs->from_file("shaders/shader.vert");
  FragmentShader *fs = new FragmentShader();
  fs->from_file("shaders/shader.frag");

  ShaderProgram *program = new ShaderProgram();
  program->add_shader(vs);
  program->add_shader(fs);

  // create camera
  glm::mat4 *p_view = program->get_view_ptr();
  const bool *keys_state = main_window->get_keys_state();
  const int *mouse_changes = main_window->get_mouse_changes();
  Camera *camera = new Camera(p_view, keys_state, mouse_changes);
  float angle = 0.0f;
  float inc = 0;

  // render loop
  float delta_time = 0.0f;
  float last_time = 0.0f;
  float now;


    brick_texture->use();
  while (!main_window->should_close()) {
    now = glfwGetTime();
    delta_time = now - last_time;
    last_time = now;
    Renderer::clear();
    Renderer::draw(*mesh, *program);
    // Renderer::draw(*model, *program);
    /* Swap front and back buffers */
    if (angle >= 360)
      angle = 0;
    angle += inc;
    program->set_perspective(45.0f, main_window->get_ratio(), 0.1f, 100.0f);
    program->reset_model()
        ->translate(0.0f, 0.0f, -4.0f)
        ->rotate(angle, glm::vec3(1.0f, 1.0f, 0.0f))
        ->scale(2, 2, 2);
    ;
    camera->updateView(delta_time);
    // swap buffers
    main_window->swap_buffers();
    // poll events
    main_window->poll_events();
  }

  // clean up
  delete vs;
  delete fs;
  delete program;
  delete mesh;
  // delete model;
  delete camera;
  LOG_DEBUG("quiting..");
  return 0;
}
