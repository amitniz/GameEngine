#include "include/game_engine.h"

using namespace Odyssey;


static GameEngine* ODYSSEY_INSTANCE;

GameEngine* GameEngine::getInstance(){
    if (!ODYSSEY_INSTANCE) ODYSSEY_INSTANCE = createApp();
    return ODYSSEY_INSTANCE;
}


GameEngine::~GameEngine(){
    for(GameObject* game_obj : m_game_objects) delete game_obj;
    for(Scene* scene : m_scenes) delete scene;
    for(ShaderProgram* shader : m_shaders) delete shader;
    for(Window* window : m_windows) delete window;
}


unsigned GameEngine::addGameObject(GameObject* game_object,unsigned scene_id){
    /*
    *  TODOs: 
    * - when adding a light, loop through shaders and update the needed uniforms.
    * - when adding a shader, loop through the lights and update the needed uniforms.
    * - when adding a shader, update the projection matrix.
    */
    UNFINISHED;
    game_object->setObjectID(m_game_objects.size());
    game_object->setObjectID(this->m_current_scene);
    m_game_objects.push_back(game_object);
    return m_game_objects.size() -1;
}

GameEngine* GameEngine::addShaderProgram(){
// Default shader
    ShaderProgram* shader = (new ShaderProgram())
        ->addVertexShader("shaders/shader.vert")
        ->addFragmentShader("shaders/shader.frag");
    this->addShaderProgram(shader);
    return this;
}

GameEngine* GameEngine::addShaderProgram(ShaderProgram* shader){
    /*
    *  TODOs: 
    *  when adding a shader, loop through the lights and update the needed uniforms.
    * - when adding a shader, update the projection matrix.
    */
    UNFINISHED;
    for(Light* light: m_scenes[m_current_scene]->m_lights){
    }
    m_shaders.push_back(shader);
    return this;
}

unsigned GameEngine::addScene(const std::string &json_file){
    return this->addScene(json_file,0);
}

unsigned GameEngine::addScene(const std::string &json_file, unsigned window_id){
    Scene* scene = Scene::loadFromJson(json_file);
    return this->addScene(scene,window_id);
}
unsigned GameEngine::addScene(){
    Scene *scene = new Scene();
    return this->addScene(scene,0);
}

unsigned GameEngine::addScene(Scene* scene, unsigned window_id){
    TODO("set the window id");
    m_scenes.push_back(scene);
    printf("test scene\n");
    return m_scenes.size() -1;
}

unsigned GameEngine::addWindow(Window* window){
    m_windows.push_back(window);
    printf("test add window\n");
    return m_windows.size()-1;
}

unsigned GameEngine::addWindow(unsigned width, unsigned height){
    Window* win = new Window(width,height);
    return this->addWindow(win);
}

void GameEngine::setup(){
    printf("Welcome to Odyssey Engine");
}

void GameEngine::preRender(){}
void GameEngine::postRender(){}

void GameEngine::loop(){
    LOG_DEBUG("enter loop");
    if (m_windows.empty() || m_scenes.empty() || m_shaders.empty()){
        LOG_CRITICAL("The engine can't run without at least once window,\
                     shader and scene");
    }
    Window *main_window = m_windows[m_main_window];
    Scene *scene = m_scenes[m_current_scene];
    ShaderProgram *shader = m_shaders[0]; //TODO: needs to be binded shader
    if(!shader->isCompiled()){
        LOG_DEBUG("compile shader");
        Renderer::compileShaders(shader);
    }
    // render loop
    LOG_DEBUG("render loop..");
    if(main_window->init() != 0){
        LOG_ERROR("windows init has failed");
    }
    while (!main_window->shouldClose()) {
        /* Swap front and back buffers */
        Renderer::clearScreen();
        this->preRender(); 
        Renderer::draw(scene, shader,main_window);
        this->postRender(); 
        // swap buffers
        main_window->swapBuffers();
        // poll events
        main_window->pollEvents();
    }
    LOG_DEBUG("quiting..");
}

Window* GameEngine::getWindow(unsigned window_id){
    if(window_id >= this->m_windows.size()){
        return nullptr;
    }
    return m_windows[window_id];
}
