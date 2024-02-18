#include "include/scene.h"

Scene* Scene::addModel(Model *model){
  m_models.push_back(model);
  return this;
}

Scene* Scene::setCamera(Camera *camera){
  m_camera = camera;
  return this;
}

Scene* Scene::addLight(Light *light){
  m_lights.push_back(light);
  return this;
}

void Scene::render(float delta_time){
  for(auto model : m_models){
    model->getShader()->use();
    for (auto light: m_lights){
      //pass shader's unifroms to the light
      light->use(*model->getShader()->getUniforms());
    }
    int camera_uniform = model->getShader()->getUniformLocation("u_camera_position");
    glm::mat4* p_view = model->getShader()->getViewPtr();
    m_camera->updateView(p_view, delta_time);
    m_camera->updatePosition(camera_uniform);
    model->render();
  }
}

Scene::~Scene(){
  for (auto model: m_models) delete model;
  for (auto light: m_lights) delete light;
  if(m_camera) delete m_camera;
}
