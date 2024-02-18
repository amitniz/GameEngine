#include "include/shader.h"
#include "include/logging.h"
#include <fstream>
#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>

// ----------------------------------- Macros ---------------------------------
#define TO_RADIANS(x) (float)(x * 3.14159265f / 180.0)

// ---------------------------------- Shader ----------------------------------

void Shader::compile(void) {
  if (this->m_id) { // incase compiled already do nothing
    return;
  }
  // create shader
  this->m_id = glCreateShader(this->type);

  const GLchar *shader_code[1] = {this->m_code.c_str()};
  GLint size[1] = {(GLint)this->m_code.length()};
  // add source code
  GLCALL(glShaderSource(this->m_id, 1, shader_code, size));
  // compile shader
  GLCALL(glCompileShader(this->m_id));
  GLint res = 0;
  GLchar info_log[1024] = {0};

  // get compilation results
  GLCALL(glGetShaderiv(this->m_id, GL_COMPILE_STATUS, &res));
  if (!res) {
    GLCALL(glGetShaderInfoLog(this->m_id, sizeof(info_log), nullptr, info_log));
    LOG_ERROR("error compiling the %d shader: '%s'\n", this->m_id, info_log);
    return;
  }
}

Shader::~Shader() {
  if (this->m_id)
    GLCALL(glDeleteShader(this->m_id));
}

Shader *Shader::fromFile(const std::string &path) {
  std::ifstream file;
  file.open(path);
  if (file.is_open()) {
    this->m_code = std::string(std::istreambuf_iterator<char>(file),
                               std::istreambuf_iterator<char>());
  } else {
    // handle errors
    LOG_ERROR("failed to open %s\n", path.c_str());
  }
  LOG_DEBUG("loaded shader from: %s successfully", path.c_str());
  return this;
}

// ---------------------------- ShaderProgram ---------------------------------

ShaderProgram *ShaderProgram::init() {
  this->addVertexShader("shaders/shader.vert")
      ->addFragmentShader("shaders/shader.frag");
  return this;
}

ShaderProgram *ShaderProgram::addShader(Shader *shader) {
  this->m_shaders.push_back(shader);
  return this;
}

ShaderProgram *ShaderProgram::addVertexShader(const std::string &shader_file) {
  Shader *vs = (new VertexShader())->fromFile(shader_file);
  this->m_shaders.push_back(vs);
  return this;
}

ShaderProgram *
ShaderProgram::addFragmentShader(const std::string &shader_file) {
  Shader *fs = (new FragmentShader())->fromFile(shader_file);
  this->m_shaders.push_back(fs);
  return this;
}

void ShaderProgram::link_shaders(void) {
  for (Shader *shader : this->m_shaders) {
    GLCALL(glAttachShader(this->m_id, shader->id()));
  }
  GLCALL(glLinkProgram(this->m_id));
  GLCALL(glValidateProgram(this->m_id));
}

void ShaderProgram::compile_shaders(void) {
  for (Shader *shader : this->m_shaders) {
    shader->compile();
  }
}

ShaderProgram::ShaderProgram()
    : m_shaders(), m_compiled_and_linked(false), m_model(glm::mat4(1.0f)),
      m_projection(glm::mat4(1.0f)), m_view(glm::mat4(1.0f)),m_uniforms() {
  this->m_id = glCreateProgram();
}

void ShaderProgram::use(void) {
  if (!m_compiled_and_linked) {
    compile_shaders();
    link_shaders();
    m_compiled_and_linked = true;
    setup_uniforms_map();
  }
  GLCALL(glUseProgram(this->m_id));
  update_uniforms();
  // LOG_DEBUG("shader %d applied",m_id);
}

ShaderProgram *ShaderProgram::scale(float x, float y, float z) {
  this->m_model = glm::scale(this->m_model, glm::vec3(x, y, z));
  return this;
}

ShaderProgram *ShaderProgram::translate(float x, float y, float z) {
  this->m_model = glm::translate(this->m_model, glm::vec3(x, y, z));
  return this;
}

ShaderProgram *ShaderProgram::rotate(float degree, glm::vec3 axis) {
  this->m_model = glm::rotate(this->m_model, TO_RADIANS(degree), axis);
  return this;
}
ShaderProgram *ShaderProgram::resetModel() {
  this->m_model = glm::mat4(1.0f);
  return this;
}

void ShaderProgram::setPerspective(float field_of_view_y, float screen_ratio,
                                   float near_view, float far_view) {
  this->m_projection =
      glm::perspective(field_of_view_y, screen_ratio, near_view, far_view);
}

void ShaderProgram::setup_uniforms_map(){
  m_uniforms["model"] = getUniformLocation("u_model");
  m_uniforms["view"] = getUniformLocation("u_view");
  m_uniforms["projection"] = getUniformLocation("u_projection");
  m_uniforms["light_color"] = getUniformLocation("u_directional_light.color");
  m_uniforms["light_direction"] = getUniformLocation("u_directional_light.direction");
  m_uniforms["ambient_intensity"] = getUniformLocation("u_directional_light.ambient_intensity");
  m_uniforms["diffuse_intensity"] = getUniformLocation("u_directional_light.diffuse_intensity");
  m_uniforms["spectacular_intensity"] = getUniformLocation("u_directional_light.spectacular_intensity");
  m_uniforms["shininess"] = getUniformLocation("u_material.shininess");
  m_uniforms["camera_position"] = getUniformLocation("u_camera_position");
}

void ShaderProgram::update_uniforms() const {
  // update model
  GLCALL(glUniformMatrix4fv(this->m_uniforms.at("model"), 1, GL_FALSE,
                            glm::value_ptr(this->m_model)));
  // update view
  GLCALL(glUniformMatrix4fv(this->m_uniforms.at("view"), 1, GL_FALSE,
                            glm::value_ptr(this->m_view)));
  // update projection
  GLCALL(glUniformMatrix4fv(this->m_uniforms.at("projection"), 1, GL_FALSE,
                            glm::value_ptr(this->m_projection)));
}
