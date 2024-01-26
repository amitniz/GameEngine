#include <GL/glew.h>
#include <fstream>
#include <iterator>

#include "include/shader.h"

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
  glShaderSource(this->m_id,1,shader_code,size);
  //compile shader
  glCompileShader(this->m_id);
  GLint res = 0;
  GLchar info_log[1024] = {0};

  //get compilation results
  glGetShaderiv(this->m_id,GL_COMPILE_STATUS, &res);
  if(!res){
    glGetShaderInfoLog(this->m_id,sizeof(info_log),nullptr, info_log);
    printf("error compiling the %d shader: '%s'\n",this->m_id,info_log);
    return;
  }
  printf("compiled shader %u\n",this->m_id);
}

Shader::~Shader(){
  if(this->m_id) glDeleteShader(this->m_id);
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
    glAttachShader(this->m_id, shader->id());
  }
  glLinkProgram(this->m_id);
  glValidateProgram(this->m_id);
  //TODO: add error handling
  return this;
}


ShaderProgram* ShaderProgram::compile_shaders(void){
  for (Shader* shader : this->m_shaders){
    shader->compile();
  }
  return this;
}

ShaderProgram::ShaderProgram():m_shaders(){
  this->m_id = glCreateProgram();
}

void ShaderProgram::use(void){
  this->compile_shaders();
  this->link_shaders();
  glUseProgram(this->m_id);
}

