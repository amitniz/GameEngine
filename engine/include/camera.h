#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include "game_object.h"

namespace Odyssey{

#define MAX_PITCH 89.0f
#define MIN_PITCH -89.0f

class Camera: public GameObject {
public:
    Camera();
    ~Camera() = default;

    void updateView(float delta_time);
    static Camera *loadFromJson(const std::string &json_string);
    inline const glm::mat4& getView() const {return m_view_matrix;}
    void updatePosition(int camera_uniform_id);
    glm::mat4 getPerspective(float window_ratio);

private:
    void keyboardController(const bool *keys_state, float delta_time);
    void mouseController(int x_change, int y_change);
    glm::vec3 position, front, up, right, world_up;
    float yaw, pitch, move_speed, turn_speed, roll;
    glm::mat4 m_view_matrix;
    glm::mat4 m_projection_matrix;
    float m_window_ratio;

};
};
