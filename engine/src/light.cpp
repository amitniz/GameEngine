#include "include/light.h"
#include "GL/glew.h"
#include "include/logging.h"
#include <glm/fwd.hpp>

using namespace Odyssey;

Light::Light() : Light(glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 1.0f) {}

Light::Light(glm::vec3 color, float ambient_intensity, float diffuse_intensity)
    : m_color(color), m_ambient_intensity(ambient_intensity),
      m_diffuse_intensity(diffuse_intensity) {}

Light *Light::setColor(glm::vec3 color) {
  m_color = color;
  return this;
}

Light *Light::setAmbientLight(float intensity) {
  m_ambient_intensity = intensity;
  return this;
}

Light *Light::setDiffuseLight(float intensity) {
  m_diffuse_intensity = intensity;
  return this;
}

void DirectionalLight::use(const map<string, int> &shader_uniforms) {
  int uniform;
  if ((uniform = shader_uniforms.at("light_color")) > 0) {
    GLCALL(glUniform3f(uniform, m_color.x, m_color.y, m_color.z));
  }
  if ((uniform = shader_uniforms.at("ambient_intensity")) > 0) {
    GLCALL(glUniform1f(uniform, m_ambient_intensity));
  }
  if ((uniform = shader_uniforms.at("diffuse_intensity")) > 0) {
    GLCALL(glUniform1f(uniform, m_diffuse_intensity));
  }
  if ((uniform = shader_uniforms.at("light_direction")) > 0) {
    GLCALL(glUniform3f(uniform, m_direction.x, m_direction.y, m_direction.z));
  }
}

DirectionalLight::DirectionalLight()
    : m_direction(glm::vec3(0., -1., 1.)), Light() {}

DirectionalLight *DirectionalLight::setDirection(glm::vec3 direction) {
  m_direction = direction;
  return this;
}
