#pragma once

#ifdef ODYSSEY_ENGINE

extern Odyssey::GameEngine* Odyssey::createApp();

int main(int argc, char* argv[]){

    auto app = Odyssey::createApp();
    app->setup();
    app->loop();
    delete app;
}

#endif


