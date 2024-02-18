#pragma once

#include "shader.h"
#include "texture.h"

/**
 * Material
 * An object that contains a Texture and a ProgramShader.
 */
class Material {
public:
  Material();
  Material(const std::string &texture_path,
           const std::string &vertex_shader_path,
           const std::string &fragment_shader_path);
  Material(const std::string &texture_path);
  ~Material();

  ShaderProgram* getShaderProgram() const {return m_shader_program; }

  /* @brief
   * applies the material to the current used model.
   */
  void use();
  void useTexture() {if(this->m_texture) m_texture->use();}
  void useShader() {if(this->m_shader_program) m_shader_program->use();}
  Material* setTexture(Texture* texture);
  Material* setShininess(float shininess);
  float getShininess() const {return m_shininess;}
  bool loadTexture();

private:
  ShaderProgram *m_shader_program;
  Texture *m_texture;
  float m_shininess;
};
