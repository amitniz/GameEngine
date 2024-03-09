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

    static Scene* loadFromJson(const std::string &json_file);
    Scene* addGameObject(GameObject *game_object); //TODO

    Scene* addModel(Model *model);
    Scene* addModel(const std::string&  json_string);

    Scene* setCamera(Camera *camera);
    Scene* setCamera(const std::string&  json_string);

    Scene* addLight(Light *light);
    Scene* addLight(const std::string&  json_string);
private:
    std::string m_name;
    unsigned m_scene_id;
    std::vector<Model*> m_models;
    std::vector<Light*> m_lights;
    Camera* m_camera;

    friend class GameEngine;
    friend class Renderer;
};
};
