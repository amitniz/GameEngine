/*/
* This code contains an abstraction layer to the OpenGL API used for rendering objects.
* In the future I might add support for other graphic frameworks.
*/
#pragma once

#include "shader.h"
#include "mesh.h"
#include "model.h"
#include "window.h"
#include "scene.h"
#include "logging.h"
#include <GL/gl.h>

namespace Odyssey{

struct OpenGLBuffersIDs;

class Renderer{
    static float last_draw_time;
public:
    Renderer() = delete;

    static void draw(Mesh* mesh);
    static void draw(Model* model, ShaderProgram* shader);
    static void draw(Scene* scene, ShaderProgram* shader,Window* window);

    static void applyMaterial(Material *Material, ShaderProgram *shader);
    static void applyLight(Light *Light, ShaderProgram *shader);


    static void updateMVP(const glm::mat4x4 &mvp_matrix, ShaderProgram* shader);

    static void deleteMesh(Mesh* mesh);
  
    static void createTexture(Texture* texture);
    static void bindTexture(Texture* texture);
    static void bindTexture(Material* material);
    static void bindTexture(unsigned texture_id);
    static void deleteTexture(Texture* texture);
    static void deleteTextures(unsigned *texture_ids, unsigned len);

    static void bindShader(ShaderProgram* shader_program);
    static void compileShaders(ShaderProgram* shader_program);
    static void linkShaders(ShaderProgram* shader_program);
    static void deleteShader(ShaderProgram* shader_program);

    inline static int getUniformLocation(ShaderProgram* shader, const std::string& uniform_name){
        return glGetUniformLocation(shader->m_id,uniform_name.c_str()); 
    }

    static void createShadowMap(unsigned width, unsigned height, unsigned *fbo, unsigned *shadow_map_id);
    static void writeShadowMap(unsigned fbo);
    static void readShadowMap(unsigned texture_unit, unsigned shadow_map_id);
    static void deleteShadowMap(unsigned fbo, unsigned shadow_map_id);

    static inline void clearScreen() {GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));}

private:
    static OpenGLBuffersIDs createMesh(float *vertices, unsigned *indices, unsigned n_vertices,unsigned n_indices);
};
};
