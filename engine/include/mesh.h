#pragma once

#include <GL/glew.h>
#include <vector>

namespace Odyssey{

class Mesh {

public:
    Mesh() = default;
    Mesh *create(float *verticies, unsigned *indices, unsigned n_verticies,
                 unsigned n_indices);

    inline Mesh *create(std::vector<float> &verticies,
                        std::vector<unsigned> &indicies) {
        return create(verticies.data(), indicies.data(), verticies.size(),
                      indicies.size());
    }
    ~Mesh() = default;
private:
    friend class Renderer;
    unsigned m_vao, m_vbo, m_ibo, m_indices_count
    , m_vertices_count;
    float* m_vertices;
    unsigned* m_indices;
};
};
