#pragma once

#include <glm/glm.hpp>

class AmbientLight {
public:
  AmbientLight();
  AmbientLight(float red, float green, float blue, float intensity);
  void use(unsigned color_location, unsigned intensity_location);
  ~AmbientLight() = default;

private:
  glm::vec3 m_color;
  float m_intensity;
};

class Light {
public:
  Light();
  Light(glm::vec3 color, glm::vec3 direction, float ambient_intensity,
        float diffuse_intensity);
  void use(unsigned color_location, unsigned ambient_intensity_location,
           unsigned diffuse_intensity_location, unsigned direction_location);
  ~Light() = default;

private:
  glm::vec3 m_color, m_direction;
  float m_ambient_intensity, m_diffuse_intensity;
};
