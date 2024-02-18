#pragma once

#include <map>
#include <string>
#include <glm/glm.hpp>

using std::string;
using std::map;

class Light {
public:
  Light();
  Light(glm::vec3 color, float ambient_intensity, float diffuse_intensity);
  virtual ~Light() = default;

  virtual void use(const map<string,int>& shader_uniforms) = 0 ;

  Light *setColor(glm::vec3 color);
  Light *setAmbientLight(float intensity);
  Light *setDiffuseLight(float intensity);

protected:
  glm::vec3 m_color;
  float m_ambient_intensity, m_diffuse_intensity;
};

class DirectionalLight : public Light {
public:
  DirectionalLight();
  ~DirectionalLight() = default;
  DirectionalLight* setDirection(glm::vec3 direction);
  virtual void use(const map<string,int>& shader_uniforms);
private:
  glm::vec3 m_direction;
};
