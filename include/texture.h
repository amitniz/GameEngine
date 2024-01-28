#pragma once


#include <string>

class Texture{

public:
    Texture();
    Texture(const std::string& m_file_path);
    ~Texture();
    Texture* load();
    void use() const;
    void clear()const;
private:
    unsigned m_id;
    int m_width, m_height,m_bit_depth;
    const std::string m_file_path;
};
