#pragma once

#include <GL/glew.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>


namespace Odyssey{

// --------------------------------- Shader -----------------------------------
class Shader {
public:

    ~Shader() = default;

    /**
   * @brief
   * create a shader from a shader file
   * @param[in] path to shader file
   * @return a pointer to the instance
   */
    Shader *fromFile(const std::string &path);

    /**
   * @brief
   * getter to the shader id
   * @return the shader id
   */
    inline unsigned int getId() const { return this->m_id; }

    /**
   * @brief
   * getter to the shader source code
   * @return the shader source code
   */
    inline const std::string & getCode() const { return this->m_code; }

private:
    std::string m_code;
    unsigned int m_id;
    friend class Renderer; // compiling is done by the renderer

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

    ShaderProgram* addVertexShader(const std::string &shader_file);

    ShaderProgram* addFragmentShader(const std::string &shader_file);

    /**
   * @brief
   * getter to the program id
   * @return the program id
   */
    inline unsigned int getId() const { return this->m_id; }

    /**
   * @brief
   * gets a uniform location
   * @return the uniform location
   */
    inline int getUniformLocation(const std::string& uniform){
        return glGetUniformLocation(this->m_id, uniform.c_str());
    }

    inline bool isCompiled() const {return m_compiled_and_linked;}

    

private:
    unsigned int m_id;
    std::vector<Shader *> m_shaders;
    bool m_compiled_and_linked;
    friend class Renderer; // compiling and binding is done by the renderer
};
};
