#pragma once

class GameEngine{

  GameEngine() = delete;
  ~GameEngine() = delete;

  GameEngine* init();
  GameEngine* run();
};
