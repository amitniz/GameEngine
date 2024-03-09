#pragma once

#include <string>

namespace Odyssey{
class Texture{

public:
    Texture();
    Texture(const std::string& m_file_path);
    ~Texture() = default;
    void use() const;
    void clear() const;
private:
    friend class Renderer;
    unsigned m_id;
    int m_width, m_height,m_bit_depth;
    std::string m_file_path;
};
};
