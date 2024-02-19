#include <nlohmann/json.hpp>
#include "include/material.h"
#include "include/shader.h"
#include "include/texture.h"
#include "include/logging.h"

using namespace Odyssey;

Material::Material()
    : m_shader_program((new ShaderProgram())->init()),
    m_texture(new Texture("assets/textures/plain.png")), m_shininess(0.5f) {}

Material::Material(const std::string &texture_path)
: m_shader_program((new ShaderProgram())->init()),  m_texture(new Texture(texture_path)),m_shininess(0.5f){}

Material::Material(const std::string &texture_path,
                   const std::string &vertex_shader_path,
                   const std::string &fragment_shader_path) {

    m_texture = new Texture(texture_path);
    m_shader_program->addVertexShader(vertex_shader_path)
        ->addFragmentShader(fragment_shader_path);
    m_shininess = 0.5f;
    m_ka =0.5f;
    m_kd =0.5f;
    m_ks =0.5f;
}

Material* Material::setTexture(Texture* texture){
    if(m_texture) delete m_texture;
    m_texture = texture;
    return this;
}

void Material::use() {
    if (m_texture)
        m_texture->use();
    if (m_shader_program)
        m_shader_program->use();
}

bool Material::loadTexture() {
    if (m_texture)
        return m_texture->load();
    return false;
}

Material* Material::setShininess(float shininess){
    if(shininess >= 0.0f && shininess <= 1.0f){
        m_shininess = shininess;

        unsigned shininess_id = m_shader_program->getUniformLocation("u_material.shininess");
        GLCALL(glUniform1f(shininess_id,shininess));
    }

    return this;
}

Material::~Material() {
    delete m_shader_program;
    delete m_texture;
}
