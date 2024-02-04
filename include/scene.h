#pragma once 

#include <vector>
#include "model.h"
#include "light.h"
#include "camera.h"

class Scene{
public:
  Scene() = default;
  ~Scene();

  Scene* add_model(Model *model);
  Scene* set_camera(Camera *camera);
  Scene* add_light(Light *light);
  void render(float delta_time);
private:
  std::vector<Model*> m_models;
  std::vector<Light*> m_lights;
  Camera* m_camera;
};
