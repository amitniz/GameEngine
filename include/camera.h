#pragma once

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>

#define MAX_PITCH 89.0f
#define MIN_PITCH -89.0f

class Camera {
public:
  Camera(const bool *keys_state, const int *mouse_changes);
  ~Camera() = default;

  void updateView(glm::mat4 *p_view, float delta_time);
  void update_position(int camera_uniform_id);

private:
  void keyboard_controller(const bool *keys_state, float delta_time);
  void mouse_controller(int x_change, int y_change);
  const bool *keys_state;
    const int *mouse_changes;
  glm::vec3 position, front, up, right, world_up;
  float yaw, pitch, move_speed, turn_speed, roll;
};
