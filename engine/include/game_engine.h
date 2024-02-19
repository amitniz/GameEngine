#pragma once

#include <vector>
#include "window.h"
#include "shader.h"
#include "scene.h"
#include "renderer.h"


namespace Odyssey{
/**
* GameEngine 
* A singleton of the engine. 
* Contains all windows, scenes, gameobjects and shaders.
*
* GameEngine should be inherent by the sandbox application of the user
*/
class GameEngine{

    public:
        GameEngine(GameEngine const&) = delete; 
        void operator =(GameEngine const&) = delete;
        virtual ~GameEngine();

        static GameEngine* getInstance();

        GameEngine* addGameObject(GameObject* game_object);
        GameEngine* addScene(Scene* scene);
        GameEngine* addWindow(Window* window);
        GameEngine* addShaderProgram(ShaderProgram* shader);
        virtual void run();

    protected:
        GameEngine() = default;
    private:
        std::vector<Window*> m_windows;    
        std::vector<Scene*> m_scenes;    
        std::vector<GameObject*> m_game_objects;    
        std::vector<ShaderProgram*> m_shaders;    
    };
    
GameEngine* createApp();
};
