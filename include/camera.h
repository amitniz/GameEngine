#pragma once

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>

#define MAX_PITCH 89.0f
#define MIN_PITCH -89.0f

class Camera {
public:
  Camera(glm::mat4 *p_view, const bool *keys_state, const int *mouse_changes);
  ~Camera() = default;

  void updateView(float delta_time);

private:
  void keyboard_controller(const bool *keys_state, float delta_time);
  void mouse_controller(int x_change, int y_change);
  glm::mat4 *p_view;
  const bool *keys_state;
    const int *mouse_changes;
  glm::vec3 position, front, up, right, world_up;
  float yaw, pitch, move_speed, turn_speed, roll;
};
