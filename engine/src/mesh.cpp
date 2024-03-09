#include "include/mesh.h"
using namespace Odyssey;

Mesh *Mesh::create(float *vertices, unsigned *indices, unsigned n_vertices,
                   unsigned n_indices) {

    m_indices_count = n_indices;
    m_vertices_count = n_vertices;
    m_vertices  = vertices;
    m_indices = indices;
    return this;
}



