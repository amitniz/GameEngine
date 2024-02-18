#pragma once

#include "light.h"
#include "window.h"
#include "shader.h"
#include "model.h"
#include "scene.h"
#include "renderer.h"
#include "material.h"
#include "mesh.h"
#include "camera.h"
#include "logging.h"

class GameEngine{

  GameEngine() = delete;
  ~GameEngine() = delete;

  GameEngine* init();
  GameEngine* run();
};
