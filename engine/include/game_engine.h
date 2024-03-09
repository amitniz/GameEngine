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

        unsigned addGameObject(GameObject* game_object, unsigned scene_id);
        unsigned addScene(); //add an empty scene
        unsigned addScene(Scene* scene); // add the scene to the main window
        unsigned addScene(const std::string& scene_json); // add the scene to the main window
        unsigned addScene(const std::string& scene_json, unsigned window_id); 
        unsigned addScene(Scene* scene, unsigned window_id);
        unsigned addWindow(Window* window);
        unsigned addWindow(unsigned width, unsigned height);
        GameEngine* addShaderProgram(); //add default shader
        GameEngine* addShaderProgram(ShaderProgram* shader);
        GameEngine* addMaterial(ShaderProgram* shader);
        inline Scene* getScene() const {return this->m_scenes[m_current_scene];}
        inline Window* getWindow() const {return this->m_windows[m_main_window];}
        Window* getWindow(unsigned window_id);
        void loop();
        virtual void preRender(); // add code to the loop before rendering
        virtual void postRender();// add code to the loop after rendering
        virtual void setup();

    protected:
        GameEngine() = default;
    private:
        unsigned m_current_scene;
        unsigned m_main_window;
        unsigned m_binded_shader;
        std::vector<Window*> m_windows;    
        std::vector<Scene*> m_scenes;    
        std::vector<GameObject*> m_game_objects;    
        std::vector<ShaderProgram*> m_shaders;    
        std::vector<Material*> m_materials;    
    };
    
GameEngine* createApp();
};
