#include "include/shader.h"
#include "include/logging.h"
#include <fstream>
#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/gl.h>

using namespace Odyssey;
// ----------------------------------- Macros ---------------------------------
#define TO_RADIANS(x) (float)(x * 3.14159265f / 180.0)

// ---------------------------------- Shader ----------------------------------


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

ShaderProgram *ShaderProgram::addVertexShader(const std::string &shader_file) {
    Shader *vs = (new VertexShader())->fromFile(shader_file);
    this->m_shaders.push_back(vs);
    return this;
}

ShaderProgram * ShaderProgram::addFragmentShader(const std::string &shader_file) {
    Shader *fs = (new FragmentShader())->fromFile(shader_file);
    this->m_shaders.push_back(fs);
    return this;
}

ShaderProgram::ShaderProgram()
    : m_shaders(), m_compiled_and_linked(false),m_id(){
}


