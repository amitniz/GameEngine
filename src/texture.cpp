#define STB_IMAGE_IMPLEMENTATION
#include "include/texture.h"
#include "include/logging.h"
#include "include/stb_image.h"
#include <GL/glew.h>

Texture::Texture(const std::string &file_path)
    : m_id(0), m_width(0), m_height(0), m_bit_depth(0),
      m_file_path(file_path){};
Texture::Texture()
    : m_id(0), m_width(0), m_height(0), m_bit_depth(0), m_file_path(){};

Texture *Texture::load() {
  // stbi_set_flip_vertically_on_load(true);
  uint8_t *data = stbi_load(this->m_file_path.c_str(), &this->m_width,
                            &this->m_height, &this->m_bit_depth, 0);

  if (!data) {
    LOG_ERROR("failed to load texture from: %s", this->m_file_path.c_str());
    return this;
  }

  GLCALL(glGenTextures(1, &m_id));
  GLCALL(glBindTexture(GL_TEXTURE_2D, m_id));

  GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
  GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
  GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

  GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA,
                      GL_UNSIGNED_BYTE, data));
  GLCALL(glGenerateMipmap(GL_TEXTURE_2D));
  // unbind
  GLCALL(glBindTexture(GL_TEXTURE_2D, 0));

  // free data
  stbi_image_free(data);

  LOG_DEBUG("loaded texture from: %s successfully", this->m_file_path.c_str());
  return this;
}

void Texture::clear() const { GLCALL(glDeleteTextures(1, &m_id)); }

void Texture::use() const {
  GLCALL(glActiveTexture(GL_TEXTURE0));
  GLCALL(glBindTexture(GL_TEXTURE_2D, m_id));
}

Texture::~Texture() { clear(); }
