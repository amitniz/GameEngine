#include "include/texture.h"

using namespace Odyssey;

Texture::Texture(const std::string &file_path)
    : m_id(0), m_width(0), m_height(0), m_bit_depth(0),
    m_file_path(file_path){};
Texture::Texture()
: m_id(0), m_width(0), m_height(0), m_bit_depth(0), m_file_path(){};



