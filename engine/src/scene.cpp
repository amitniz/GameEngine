#include <fstream>
#include "include/scene.h"
#include "nlohmann/json.hpp"
using namespace Odyssey;

Scene* Scene::loadFromJson(const std::string &json_file){
    std::ifstream json_fd(json_file);

    if(!json_fd){
        LOG_ERROR("failed to read: %s", json_file.c_str());
        return nullptr;
    }
    nlohmann::json j;
    json_fd >> j;
    json_fd.close();
    
    if(j["scene"].is_null()){
        LOG_ERROR("no 'scene' field in the given json file");
        return nullptr;
    }
    Scene* scene = new Scene();

    nlohmann::json j_scene = j["scene"];
    if(!j_scene["name"].is_null()){
        scene->m_name = j_scene["name"];
    }
    
    if(!j_scene["models"].is_null()){
        for (const auto& model: j_scene["models"]){
            LOG_DEBUG("model: %s\n",model.dump().c_str());
            scene->addModel(model.dump());
        }
    }
    
    if(!j_scene["lights"].is_null()){
        for (const auto& light: j_scene["models"]){
            LOG_DEBUG("light: %s\n",light.dump().c_str());
            scene->addLight(light.dump());
        }
    }

    if(!j_scene["camera"].is_null()){
        LOG_DEBUG("camera: %s\n",j_scene["camera"].dump().c_str());
        scene->setCamera(j_scene["camera"].dump());
    }
    return scene;
}
Scene* Scene::addModel(Model *model){
    m_models.push_back(model);
    return this;
}
Scene* Scene::addModel(const std::string&  json_string){
    Model* model = Model::loadFromJson(json_string);
    return this->addModel(model);
}

Scene* Scene::setCamera(Camera *camera){
    m_camera = camera;
    return this;
}

Scene* Scene::setCamera(const std::string&  json_string){
    Camera* camera = Camera::loadFromJson(json_string);
    return this->setCamera(camera);
}


Scene* Scene::addLight(Light *light){
    m_lights.push_back(light);
    return this;
}

Scene* Scene::addLight(const std::string&  json_string){
    Light* light = Light::loadFromJson(json_string);
    return this->addLight(light);
}


Scene::~Scene(){
    TODO("see if needed here or just in the GameEngine");
    for (auto model: m_models) delete model;
    for (auto light: m_lights) delete light;
    if(m_camera) delete m_camera;
}
