#pragma once

#include "game_object.h"
#include <map>
#include <string>
#include <glm/glm.hpp>

namespace Odyssey{

using std::string;
using std::map;

class Light: public GameObject {
public:
    Light();
    Light(glm::vec3 color, float ambient_intensity, float diffuse_intensity);
    virtual ~Light() = default;

    virtual void use(const map<string,int>& shader_uniforms) = 0 ;
    static Light *loadFromJson(const std::string &json_string);

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
};
