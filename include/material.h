#pragma once

#include "shader.h"
#include "texture.h"

/* Material
 * An object that contains a Texture and a ProgramShader
 *
 * A Material can be applied to a Model.
 */

class Material {
public:
  Material();
  Material(const std::string &texture_path,
           const std::string &vertex_shader_path,
           const std::string &fragment_shader_path);
  Material(const std::string &texture_path);
  ~Material();

  ShaderProgram* get_shader_program() const {return m_shader_program; }

  /* @brief
   * applies the material to the current used model.
   */
  void use();
  void use_texture() {if(this->m_texture) m_texture->use();}
  void use_shader() {if(this->m_shader_program) m_shader_program->use();}
  Material* set_shininess(float shininess);
  float get_shininess() const {return m_shininess;}
  bool load_texture();

private:
  ShaderProgram *m_shader_program;
  Texture *m_texture;
  float m_shininess;
};
