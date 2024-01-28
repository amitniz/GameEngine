#include "include/camera.h"
#include "include/light.h"
#include "include/logging.h"
#include "include/model.h"
#include "include/renderer.h"
#include "include/shader.h"
#include "include/texture.h"
#include "include/window.h"
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>

int main() {
  LOG_DEBUG("starting the engine..");
  // create window
  Window *main_window = new Window(1920, 1080);
  main_window->init();

  // create texture
  Texture *brick_texture = new Texture("assets/textures/plain.png");
  brick_texture->load();

  // create model
  Model *model = new Model();
  model->load("assets/models/x-wing.obj");
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

  // create ambient light
  Light *light = new Light(glm::vec3(0.4,0.5,0.5),glm::vec3(0.5f,4.0f,-7.0f),1.0f,1.0f);
  // render loop
  float delta_time = 0.0f;
  float last_time = 0.0f;
  float now;

  unsigned color_location;
  unsigned ambient_intensity_location;
  unsigned diffuse_intensity_location;
  unsigned direction_location;
  brick_texture->use();
  LOG_DEBUG("render loop..");
  while (!main_window->should_close()) {
    now = glfwGetTime();
    delta_time = now - last_time;
    last_time = now;
    Renderer::clear();
    Renderer::draw(*model, *program);
    /* Swap front and back buffers */
    program->set_perspective(45.0f, main_window->get_ratio(), 0.1f, 100.0f);
    program->reset_model()
        ->translate(0.0f, 0.0f, -5.0f)
        ->scale(0.01, 0.01, 0.01);
    ;
    color_location = program->get_ambient_color();
    ambient_intensity_location = program->get_ambient_intensity();
    diffuse_intensity_location = program->get_diffuse_intensity();
        direction_location = program->get_diffuse_direction();
    light->use(color_location,ambient_intensity_location,diffuse_intensity_location,direction_location);
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
  delete light;
  delete model;
  delete camera;
  LOG_DEBUG("quiting..");
  return 0;
}
