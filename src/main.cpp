#include "include/game_engine.h"
#include "include/texture.h"

Scene* setupScene(const bool *keys_state, const int* mouse_changes, float window_ratio){

    // // create models
    Model *flight_craft = new Model();
    flight_craft->load("assets/models/x-wing.obj");
    flight_craft->translate(-74.0f, 1.0f, 87.0f);
    flight_craft->scale(0.05f, 0.05f, 0.05f);
    flight_craft->getShader()->setPerspective(45., window_ratio, .1,
                                              1000.);

    Model* sphere = new Model();
    sphere
        ->load("assets/models/sphere.obj")
        ->translate(15.,1.,7.);
    sphere->getShader()->setPerspective(45., window_ratio, .1,
                                        1000.);


    Model *plane = new Model();
    plane->load("assets/models/plane.obj");
    Texture* texture = (new Texture("assets/textures/dirt.jpg"))->load();
    plane->setTexture(texture);

    plane->getShader()->setPerspective(45., window_ratio, .1,
                                       1000.);

    // create camera
    Camera *camera = new Camera(keys_state, mouse_changes);

    // create ambient light
    Light *light = (new DirectionalLight())
        ->setDirection(glm::vec3(0., .3, .3))
        ->setAmbientLight(.5)
        ->setDiffuseLight(.7)
        ->setColor(glm::vec3(.9,.8,.6))
    ;
    // set scene
    Scene *scene = new Scene();
    scene
        ->addModel(flight_craft)
        ->addModel(sphere)
        ->addModel(plane)
        ->addLight(light)
        ->setCamera(camera)
    ;
    return scene;
}


Window *setupWindow(){
    // create window
    Window *window = new Window(1920, 1080);
    window->init();
    return window;
}


int main() {
    LOG_INFO("starting the engine..");

    Window* main_window = setupWindow();

    Scene* scene = setupScene(main_window->getKeysState(), main_window->getMouseChanges(), main_window->getRatio());

    // render loop
    LOG_DEBUG("render loop..");
    while (!main_window->shouldClose()) {
        /* Swap front and back buffers */
        Renderer::clearScreen();
        Renderer::draw(*scene);
        // swap buffers
        main_window->swapBuffers();
        // poll events
        main_window->pollEvents();
    }

    // clean up
    delete scene;
    LOG_DEBUG("quiting..");
    return 0;
}
