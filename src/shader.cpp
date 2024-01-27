#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include "include/shader.h"
#include "include/logging.h"


// ----------------------------------- Macros ---------------------------------
#define TO_RADIANS(x) (float)(x * 3.14159265f/180.0)

// ---------------------------------- Shader ----------------------------------

void Shader::compile(void){
  if(this->m_id){ //incase compiled already do nothing
    return; 
  }
  //create shader
  this->m_id = glCreateShader(this->type);

  const GLchar* shader_code[1] = {this->m_code.c_str()};
  GLint size[1] = {(GLint) this->m_code.length()};
  //add source code
  GLCALL(glShaderSource(this->m_id,1,shader_code,size));
  //compile shader
  GLCALL(glCompileShader(this->m_id));
  GLint res = 0;
  GLchar info_log[1024] = {0};

  //get compilation results
  GLCALL(glGetShaderiv(this->m_id,GL_COMPILE_STATUS, &res));
  if(!res){
    GLCALL(glGetShaderInfoLog(this->m_id,sizeof(info_log),nullptr, info_log));
    printf("error compiling the %d shader: '%s'\n",this->m_id,info_log);
    return;
  }
}

Shader::~Shader(){
  if(this->m_id) GLCALL(glDeleteShader(this->m_id));
}

Shader* Shader::from_file(const std::string& path){
  std::ifstream file;
  file.open(path);
  if (file.is_open()){
    this->m_code = std::string(std::istreambuf_iterator<char>(file),std::istreambuf_iterator<char>());
  }
  else{
    //handle errors
    printf("failed to open %s\n",path.c_str());
  }
  return this;
}

// ---------------------------- ShaderProgram ---------------------------------

ShaderProgram* ShaderProgram::add_shader(Shader* shader){
  this->m_shaders.push_back(shader);
  return this;
}

ShaderProgram* ShaderProgram::link_shaders(void){
  for (Shader* shader : this->m_shaders){
    GLCALL(glAttachShader(this->m_id, shader->id()));
  }
  GLCALL(glLinkProgram(this->m_id));
  GLCALL(glValidateProgram(this->m_id));
  return this;
}


ShaderProgram* ShaderProgram::compile_shaders(void){
  for (Shader* shader : this->m_shaders){
    shader->compile();
  }
  return this;
}

ShaderProgram::ShaderProgram():m_shaders(),compiled_and_linked(false),m_model(glm::mat4(1.0f)),m_projection(glm::mat4(1.0f)){
  this->m_id = glCreateProgram();
}

void ShaderProgram::use(void){
  if(!this->compiled_and_linked){
    this->compile_shaders();
    this->link_shaders();
    this->compiled_and_linked = true;
  }
  GLCALL(glUseProgram(this->m_id));
  //update model
  GLCALL(glUniformMatrix4fv(this->get_model(),1,GL_FALSE,glm::value_ptr(this->m_model)));
  //update projection
  GLCALL(glUniformMatrix4fv(this->get_projection(),1,GL_FALSE,glm::value_ptr(this->m_projection)));
}

ShaderProgram* ShaderProgram::scale(float x, float y, float z) {
  this->m_model = glm::scale(this->m_model,glm::vec3(x,y,z));
  return this;
}

ShaderProgram* ShaderProgram::translate(float x, float y, float z) {
  this->m_model = glm::translate(this->m_model,glm::vec3(x,y,z));
  return this;
}

ShaderProgram* ShaderProgram::rotate(float degree, glm::vec3 axis) {
  this->m_model = glm::rotate(this->m_model,TO_RADIANS(degree),axis);
  return this;
}
ShaderProgram* ShaderProgram::reset_model(){
  this->m_model = glm::mat4(1.0f);
  return this;
}

void ShaderProgram::set_perspective(float field_of_view_y, float screen_ratio,float near_view,float far_view){
  this->m_projection = glm::perspective(field_of_view_y,screen_ratio,near_view,far_view);
}
