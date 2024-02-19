#include "include/game_engine.h"

using namespace Odyssey;

GameEngine* GameEngine::getInstance(){
    //TODO make sure cannot be called twice
    static GameEngine* INSTANCE = new GameEngine;
    return INSTANCE;
}


GameEngine::~GameEngine(){
    for(GameObject* game_obj : m_game_objects) delete game_obj;
    for(Scene* scene : m_scenes) delete scene;
    for(ShaderProgram* shader : m_shaders) delete shader;
    for(Window* window : m_windows) delete window;
}


GameEngine* GameEngine::addGameObject(GameObject* game_object){
    game_object->m_object_id = m_game_objects.size();
    m_game_objects.push_back(game_object);
    return this;
}

GameEngine* GameEngine::addShaderProgram(ShaderProgram* shader){
    m_shaders.push_back(shader);
    return this;
}

GameEngine* GameEngine::addScene(Scene* scene){
    m_scenes.push_back(scene);
    return this;
}

GameEngine* GameEngine::addWindow(Window* window){
    m_windows.push_back(window);
    return this;
}

void GameEngine::run(){
    printf("Welcome to Odyssey Engine");
}
