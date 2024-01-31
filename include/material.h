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

  const ShaderProgram* get_shader_program() const {return m_shader_program; }

  /* @brief
   * applies the material to the current used model.
   */
  void use();

  bool load_texture();

private:
  ShaderProgram *m_shader_program;
  Texture *m_texture;
};
