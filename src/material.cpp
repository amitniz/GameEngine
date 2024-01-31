#include "include/material.h"
#include "include/shader.h"
#include "include/texture.h"

Material::Material()
    : m_shader_program(nullptr),
      m_texture(new Texture("assets/textures/plain.png")) {}

Material::Material(const std::string &texture_path)
    : m_shader_program(nullptr) {
  m_texture = new Texture(texture_path);
}

Material::Material(const std::string &texture_path,
                   const std::string &vertex_shader_path,
                   const std::string &fragment_shader_path) {

  m_texture = new Texture(texture_path);

  VertexShader *vs = new VertexShader();
  vs->from_file(vertex_shader_path);

  FragmentShader *fs = new FragmentShader();
  fs->from_file(fragment_shader_path);

  m_shader_program->add_shader(vs);
  m_shader_program->add_shader(fs);
}

void Material::use() {
  if (m_texture) m_texture->use();
  if (m_shader_program) m_shader_program->use();
}

bool Material::load_texture(){
  if(m_texture) return m_texture->load();
  return false;
}

Material::~Material(){
  delete m_shader_program;
  delete m_texture;
}

