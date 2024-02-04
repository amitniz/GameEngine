#include "include/camera.h"
#include "include/light.h"
#include "include/logging.h"
#include "include/model.h"
#include "include/renderer.h"
#include "include/scene.h"
#include "include/shader.h"
#include "include/window.h"
#include <assimp/Importer.hpp>

int main() {
  LOG_DEBUG("starting the engine..");
  // create window
  Window *main_window = new Window(1920, 1080);
  main_window->init();

  // create model
  Model *model = new Model();
  model->load("assets/models/sphere.obj");
  model->translate(0.0f, 5.0f, 0.0f);
  // model->scale(0.01f, 0.01f, 0.01f);
  model->get_shader()->set_perspective(45.0f, main_window->get_ratio(), 0.1f,
                                       100.0f);

  // create camera
  const bool *keys_state = main_window->get_keys_state();
  const int *mouse_changes = main_window->get_mouse_changes();
  Camera *camera = new Camera(keys_state, mouse_changes);

  // create ambient light
  Light *light = new Light(glm::vec3(1.0, 0.3, 0.4),
                           glm::vec3(0.0f, 1.0f, 1.0f), 0.3f, 0.5f);

  // set scene
  Scene *scene = new Scene();
  scene->add_model(model)->add_light(light)->set_camera(camera);

  // render loop
  LOG_DEBUG("render loop..");
  while (!main_window->should_close()) {
    /* Swap front and back buffers */
    Renderer::clear();
    Renderer::draw(*scene);
    // swap buffers
    main_window->swap_buffers();
    // poll events
    main_window->poll_events();
  }

  // clean up
  delete scene;
  LOG_DEBUG("quiting..");
  return 0;
}
