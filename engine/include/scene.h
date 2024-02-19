#pragma once 

#include <vector>
#include "game_object.h"
#include "model.h"
#include "light.h"
#include "camera.h"

namespace Odyssey{
class Scene{
public:
    Scene() = default;
    ~Scene();

    Scene* addGameObject(GameObject *game_object);
    Scene* addModel(Model *model);
    Scene* setCamera(Camera *camera);
    Scene* addLight(Light *light);
    void render(float delta_time);
private:
    std::vector<Model*> m_models;
    std::vector<Light*> m_lights;
    Camera* m_camera;
};
};
