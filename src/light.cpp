#include "include/light.h"
#include "GL/glew.h"
#include "include/logging.h"
#include <glm/fwd.hpp>

Light::Light()
    : Light(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f), 1.0f,
            1.0f) {}

Light::Light(glm::vec3 color, glm::vec3 direction, float ambient_intensity,
             float diffuse_intensity):m_color(color),m_direction(direction),m_ambient_intensity(ambient_intensity),m_diffuse_intensity(diffuse_intensity) {}

void Light::use(unsigned color_location, unsigned ambient_intensity_location,
                unsigned diffuse_intensity_location, unsigned direction_location) {
  GLCALL(glUniform3f(color_location, m_color.x, m_color.y, m_color.z));
  GLCALL(glUniform1f(ambient_intensity_location, m_ambient_intensity));
  GLCALL(glUniform1f(diffuse_intensity_location, m_diffuse_intensity));
  GLCALL(glUniform3f(direction_location, m_direction.x,m_direction.y,m_direction.z));
}
