#pragma once

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <map>

// --------------------------------- Shader -----------------------------------

class Shader {
public:

  ~Shader();

  /**
   * @brief
   * create a shader from a shader file
   * @param[in] path to shader file
   * @return a pointer to the instance
   */
  Shader *fromFile(const std::string &path);

  /**
   * @brief
   * compile the shader
   */
  void compile(void);

  /**
   * @brief
   * getter to the shader id
   * @return the shader id
   */
  inline unsigned int id() const { return this->m_id; }

  /**
   * @brief
   * getter to the shader source code
   * @return the shader source code
   */
  inline const std::string &code() const { return this->m_code; }

private:
  std::string m_code;
  unsigned int m_id;

protected:
  inline Shader() : m_code(), m_id(0) {}
  unsigned int type;
};

class VertexShader : public Shader {
public:
  inline VertexShader() : Shader() { this->type = GL_VERTEX_SHADER; }
};
class FragmentShader : public Shader {
public:
  inline FragmentShader() : Shader() { this->type = GL_FRAGMENT_SHADER; }
};

// ------------------------------ ShaderProgram -------------------------------

//TODO: ShaderProgram should have a destructor or at least storing memebers by value
class ShaderProgram {
public:
  ShaderProgram();
  
  ShaderProgram* init(); //default shader program
  ShaderProgram* addShader(Shader *shader);

  ShaderProgram* addVertexShader(const std::string &shader_file);

  ShaderProgram* addFragmentShader(const std::string &shader_file);

  /**
   * @brief
   * compiles and links shaders and use the shader program
   */
  void use(void);

  /**
   * @brief
   * getter to the program id
   * @return the program id
   */
  inline unsigned int id() const { return this->m_id; }

  /**
   * @brief
   * gets a uniform location
   * @return the uniform location
   */
  inline int getUniformLocation(const std::string& uniform){
    return glGetUniformLocation(this->m_id, uniform.c_str());
  }

  inline const std::map<std::string,int>* getUniforms() const{
    return &m_uniforms;
  }
  // model manipulations
  ShaderProgram *resetModel();
  ShaderProgram *scale(float x, float y, float z);
  ShaderProgram *translate(float x, float y, float z);
  ShaderProgram *rotate(float degree, glm::vec3 axis);

    inline glm::mat4* getViewPtr() {return &m_view;}
  void setPerspective(float field_of_view_y, float screen_ratio,
                       float near_view, float far_view);

private:
  void link_shaders(void);
  void compile_shaders(void);
  void update_uniforms() const;
  void setup_uniforms_map();
  unsigned int m_id;
  std::vector<Shader *> m_shaders;
  bool m_compiled_and_linked;
  glm::mat4 m_model, m_projection, m_view;
  std::map<std::string,int> m_uniforms;
};
