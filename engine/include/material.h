#pragma once

#include "shader.h"
#include "texture.h"

/**
 * Material
 * An object that contains a Texture and a ProgramShader.
 */
namespace Odyssey{
class Material {
public:
    Material() = default;
    ~Material() = default;

    inline Material* addTexture(const std::string &texture_file){this->m_texture_file = texture_file; return this;}
    static Material* load(const std::string &json_file);
    inline float getShininess() const {return m_shininess;}
    inline const std::string & getTextureFile() const {return m_texture_file;}
    inline unsigned getId() const {return m_id;}

protected:
    unsigned m_id; // texture id 
    friend class Renderer;
private:
    std::string m_texture_file;
    float m_shininess;
    float m_ka;
    float m_kd;
    float m_ks;
};
};
