#include "include/scene.h"
#include "include/logging.h"


Scene* Scene::add_model(Model *model){
  m_models.push_back(model);
  return this;
}

Scene* Scene::set_camera(Camera *camera){
  m_camera = camera;
  return this;
}

Scene* Scene::add_light(Light *light){
  m_lights.push_back(light);
  return this;
}

void Scene::render(float delta_time){
  for(auto model : m_models){
    model->get_shader()->use();
    for (auto light: m_lights){
      unsigned ambient_color = model->get_shader()->get_ambient_color();
      unsigned ambient_intensity = model->get_shader()->get_ambient_intensity();
      unsigned diffuse_intensity = model->get_shader()->get_diffuse_intensity();
      unsigned diffuse_direction = model->get_shader()->get_diffuse_direction();
      
    
      light->use(ambient_color, ambient_intensity, diffuse_intensity, diffuse_direction);
    }
    int camera_uniform = model->get_shader()->get_camera_position();
    glm::mat4* p_view = model->get_shader()->get_view_ptr();
    m_camera->updateView(p_view, delta_time);
    m_camera->update_position(camera_uniform);
    model->render();
  }
}

Scene::~Scene(){
  for (auto model: m_models) delete model;
  for (auto light: m_lights) delete light;
  if(m_camera) delete m_camera;
}
