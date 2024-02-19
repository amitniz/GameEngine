#pragma once

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include "game_object.h"

namespace Odyssey{

#define MAX_PITCH 89.0f
#define MIN_PITCH -89.0f

class Camera: public GameObject {
public:
    Camera(const bool *keys_state, const int *mouse_changes);
    ~Camera() = default;

    void updateView(glm::mat4 *p_view, float delta_time);
    void updatePosition(int camera_uniform_id);

private:
    void keyboardController(const bool *keys_state, float delta_time);
    void mouseController(int x_change, int y_change);
    const bool *keys_state;
    const int *mouse_changes;
    glm::vec3 position, front, up, right, world_up;
    float yaw, pitch, move_speed, turn_speed, roll;
};
};
