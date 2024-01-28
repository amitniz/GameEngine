#include "include/camera.h"
#include "glm/ext/matrix_transform.hpp"
#include "include/logging.h"
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>

void Camera::keyboard_controller(const bool *keys_states, float delta_time) {

  // calculate velocity according to deltatime
  float velocity = this->move_speed * delta_time;

  // update position according to recent keyboard events
  if (keys_states['w'] || keys_states['W']) {
    position += front * velocity;
  }
  if (keys_states['s'] || keys_states['S']) {
    position -= front * velocity;
  }
  if (keys_states['a'] || keys_states['A']) {
    position -= right * velocity;
  }
  if (keys_states['d'] || keys_states['D']) {
    position += right * velocity;
  }
  // TODO limit roll between -180 and 180
  if (keys_states['e'] || keys_states['E']) {
    this->roll = this->roll - this->turn_speed*5;
  }
  if (keys_states['q'] || keys_states['Q']) {
    this->roll = this->roll + this->turn_speed*5;
  }
}

void Camera::mouse_controller(int x_change, int y_change) {
  x_change *= this->turn_speed;
  y_change *= this->turn_speed;

  yaw += x_change;
  pitch -= y_change;

  // prevent looking up to high
  if (this->pitch >= MAX_PITCH)
    pitch = MAX_PITCH;
  if (this->pitch <= MIN_PITCH)
    pitch = MIN_PITCH;

  // update position matrix

  // calculate the front vector
  this->front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
  this->front.y = sin(glm::radians(this->pitch));
  this->front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
  this->front = glm::normalize(front);

  // update world up
  this->world_up.y = cos(glm::radians(this->roll));
  this->world_up.x = sin(glm::radians(this->roll));
  this->world_up = glm::normalize(this->world_up);
  // update the relative right and up
  this->right = glm::normalize(glm::cross(this->front, this->world_up));
  this->up = glm::normalize(glm::cross(this->right, this->front));
}

void Camera::updateView(float delta_time) {
  mouse_controller(this->mouse_changes[0], this->mouse_changes[1]);
  keyboard_controller(this->keys_state, delta_time);
  *this->p_view = glm::lookAt(position, position + front, up);
}

Camera::Camera(glm::mat4 *p_view, const bool *keys_state,
               const int mouse_changes[2])
    : p_view(p_view), keys_state(keys_state), mouse_changes(mouse_changes) {
  this->position = glm::vec3(0.0f, 5.0f, 5.0f);
  this->world_up = glm::vec3(0.0f, 1.0f, 0.0f);
  this->front = glm::vec3(0.0f, -5.0f, 1.0f);
  this->pitch = 0.0f;
  this->yaw = -90.0f;
  this->roll = 0.0f;
  this->move_speed = 5.0f;
  this->turn_speed = 0.4f;
}
