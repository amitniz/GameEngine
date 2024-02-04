#include "include/material.h"
#include "include/shader.h"
#include "include/texture.h"
#include "include/logging.h"

Material::Material()
    : m_shader_program((new ShaderProgram())->init()),
      m_texture(new Texture("assets/textures/plain.png")), m_shininess(0.5f) {}

Material::Material(const std::string &texture_path)
    : m_shader_program((new ShaderProgram())->init()),  m_texture(new Texture(texture_path)),m_shininess(0.5f){}

Material::Material(const std::string &texture_path,
                   const std::string &vertex_shader_path,
                   const std::string &fragment_shader_path) {

  m_texture = new Texture(texture_path);
  m_shader_program->add_vertex_shader(vertex_shader_path)
                  ->add_fragment_shader(fragment_shader_path);
  m_shininess = 0.5f;
}

void Material::use() {
  if (m_texture)
    m_texture->use();
  if (m_shader_program)
    m_shader_program->use();
}

bool Material::load_texture() {
  if (m_texture)
    return m_texture->load();
  return false;
}

Material* Material::set_shininess(float shininess){
  if(shininess >= 0.0f && shininess <= 1.0f){
    m_shininess = shininess;
    
    unsigned shininess_id = m_shader_program->get_shininess();
    GLCALL(glUniform1f(shininess_id,shininess));
  }

  return this;
}

Material::~Material() {
  delete m_shader_program;
  delete m_texture;
}
