#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"
#include "include/renderer.h"
#include "include/logging.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

using namespace Odyssey;
float Renderer::last_draw_time;

struct Odyssey::OpenGLBuffersIDs{
    OpenGLBuffersIDs(unsigned vao,unsigned ibo,unsigned vbo);
    unsigned vao;
    unsigned ibo;
    unsigned vbo;
};

OpenGLBuffersIDs::OpenGLBuffersIDs(unsigned vao, unsigned ibo, unsigned vbo)
: vao(vao), ibo(ibo), vbo(vbo) {}

// ------------------------------------ Mesh ----------------------------------

void Renderer::draw(Mesh *mesh){
    // create if not created
    if (!mesh->m_vao){
        OpenGLBuffersIDs mesh_ids = createMesh(mesh->m_vertices,mesh->m_indices, mesh->m_vertices_count, mesh->m_indices_count);
        mesh->m_vao = mesh_ids.vao;
        mesh->m_vbo = mesh_ids.vbo;
        mesh->m_ibo = mesh_ids.ibo;
    }
    // bind vao
    GLCALL(glBindVertexArray(mesh->m_vao));
    // bind ibo
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->m_ibo));
    // draw mesh
    GLCALL(glDrawElements(GL_TRIANGLES, mesh->m_indices_count, GL_UNSIGNED_INT, 0));
    // unbind ibo
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    // unbind vao
    GLCALL(glBindVertexArray(0));
}


OpenGLBuffersIDs Renderer::createMesh(float *vertices, unsigned *indices,
                                      unsigned n_vertices, unsigned n_indices) {
    unsigned vao, vbo, ibo;

    // vao
    GLCALL(glGenVertexArrays(1, &vao));
    GLCALL(glBindVertexArray(vao));
    // ibo
    GLCALL(glGenBuffers(1, &ibo));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * n_indices,
                        indices, GL_STATIC_DRAW));
    // vbo
    GLCALL(glGenBuffers(1, &vbo));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * n_vertices,
                        vertices, GL_STATIC_DRAW));

    // positions attribute
    GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                                 sizeof(vertices[0]) * 8, 0));
    GLCALL(glEnableVertexAttribArray(0));
    // Textures attribute
    GLCALL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
                                 sizeof(vertices[0]) * 8,
                                 (void *)(sizeof(vertices[0]) * 3)));
    GLCALL(glEnableVertexAttribArray(1));
    // normals attribute
    GLCALL(glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE,
                                 sizeof(vertices[0]) * 8,
                                 (void *)(sizeof(vertices[0]) * 5)));
    GLCALL(glEnableVertexAttribArray(2));

    // unbinds
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));         // unbind vbo
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); // unbind ibo

    GLCALL(glBindVertexArray(0)); // unbind vao

    return OpenGLBuffersIDs(vao, ibo, vbo);
}

void Renderer::deleteMesh(Mesh *mesh){

    if (!mesh->m_ibo) {
        GLCALL(glDeleteBuffers(1, &mesh->m_ibo));
        mesh->m_ibo = 0;
    }
    if (!mesh->m_vbo) {
        GLCALL(glDeleteBuffers(1, &mesh->m_vbo));
        mesh->m_vbo = 0;
    }
    if (!mesh->m_vao) {
        GLCALL(glDeleteVertexArrays(1, &mesh->m_vao));
        mesh->m_vao = 0;
    }
    mesh->m_indices_count = 0;
}

// ---------------------------------- Texture ---------------------------------

void Renderer::createTexture(Texture *texture){
    if(texture->m_file_path.empty()){
        LOG_ERROR("no texture file was given.");
        return;
    }

    stbi_set_flip_vertically_on_load(true);
    uint8_t *data = stbi_load(texture->m_file_path.c_str(), &texture->m_width,
                              &texture->m_height, &texture->m_bit_depth, 0);

    if (!data) {
        LOG_ERROR("failed to load texture from: %s", texture->m_file_path.c_str());
        return;
    }

    GLCALL(glGenTextures(1, &texture->m_id));
    GLCALL(glBindTexture(GL_TEXTURE_2D, texture->m_id));

    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->m_width, texture->m_height, 0, GL_RGB,
                        GL_UNSIGNED_BYTE, data));
    GLCALL(glGenerateMipmap(GL_TEXTURE_2D));
    // unbind
    GLCALL(glBindTexture(GL_TEXTURE_2D, 0));

    // free data
    stbi_image_free(data);
    LOG_DEBUG("loaded texture from: %s successfully", texture->m_file_path.c_str());
}


void Renderer::bindTexture(Texture* texture){
    bindTexture(texture->m_id);
}

void Renderer::bindTexture(unsigned texture_id){
    GLCALL(glActiveTexture(GL_TEXTURE0));
    GLCALL(glBindTexture(GL_TEXTURE_2D, texture_id));
}

void Renderer::deleteTexture(Texture* texture){
    deleteTextures(&(texture->m_id),1);
}

void Renderer::deleteTextures(unsigned *texture_ids,unsigned len){
    GLCALL(glDeleteTextures(len, texture_ids));
}

// ---------------------------------- Material --------------------------------

void Renderer::bindTexture(Material* material){
    if(material->m_id == 0){
        const std::string texture = material->getTextureFile();
        if (texture.empty()){
            LOG_DEBUG("no texture in the given material");
            return;
        }
        Texture tex = Texture(texture);
        createTexture(&tex);
        material->m_id = tex.m_id; //store the m_id of the texture
    }else{
        bindTexture(material->m_id); //bind with texture id
    }

}




// ----------------------------------- Model ----------------------------------
void Renderer::draw(Model *model, ShaderProgram* shader) {
    for (int i = 0; i < model->m_meshes.size(); i++) {
        unsigned material_idx = model->m_mesh_2_tex[i];
        if (material_idx < model->m_materials.size() && model->m_materials[material_idx]) {
            Material *material = model->m_materials[material_idx];
            bindTexture(material);
            applyMaterial(material,shader);
        }
        draw(model->m_meshes[i]);
    }
}
// ----------------------------------- Light ----------------------------------
// ----------------------------------- Window ---------------------------------

// ----------------------------------- Scene ----------------------------------
void Renderer::draw(Scene *scene, ShaderProgram* shader,Window *window) { 
    if(scene->m_camera == nullptr){
        LOG_CRITICAL("scene has no camera");
        return;
    }
    // projection matrix
    const glm::mat4 &projection_matrix = scene->m_camera->getPerspective(window->getRatio());
    // view matrix
    const glm::mat4 &view_matrix = scene->m_camera->getView();

    for(auto model : scene->m_models){
        // model matrix
        const glm::mat4 &model_matrix = model->getModel();
        // calculate mvp
        glm::mat4 mvp_matrix = projection_matrix * view_matrix * model_matrix;
        // update the mvp matrix in the shader
        Renderer::updateMVP(mvp_matrix,shader);
        //render model
        Renderer::draw(model,shader);
    }
}


// ----------------------------------- Shader ---------------------------------

void Renderer::bindShader(ShaderProgram* shader_program){
    //lazy compiling
    if(!shader_program->isCompiled()){
        Renderer::compileShaders(shader_program);
        Renderer::linkShaders(shader_program);
        shader_program->m_compiled_and_linked = true;
    }
    GLCALL(glUseProgram(shader_program->m_id));
}

void Renderer::updateMVP(const glm::mat4x4 &mvp_matrix, ShaderProgram* shader){
    int mvp_uniform = glGetUniformLocation(shader->m_id, "u_mvp");
    GLCALL(glUniformMatrix4fv(mvp_uniform,1,false,glm::value_ptr(mvp_matrix))); 
}

void Renderer::applyMaterial(Material *Material, ShaderProgram *shader){
    UNFINISHED;
}
void Renderer::compileShaders(ShaderProgram* shader_program){
    for(Shader* shader : shader_program->m_shaders){
        shader->m_id = glCreateShader(shader->type); 
        if (!shader->m_id){
            LOG_CRITICAL("failed to generate a shader");
        }

        const GLchar *shader_code[1] = {shader->m_code.c_str()};
        GLint size[1] = {(GLint)shader->m_code.length()};
        // add source code
        GLCALL(glShaderSource(shader->m_id, 1, shader_code, size));
        // compile shader
        GLCALL(glCompileShader(shader->m_id));
        GLint res = 0;
        GLchar info_log[1024] = {0};

        // get compilation results
        GLCALL(glGetShaderiv(shader->m_id, GL_COMPILE_STATUS, &res));
        if (!res) {
            GLCALL(glGetShaderInfoLog(shader->m_id, sizeof(info_log), nullptr, info_log));
            LOG_ERROR("error compiling the %d shader: '%s'\n", shader->m_id, info_log);
            return;
        }

    }
}

void Renderer::linkShaders(ShaderProgram* shader_program){
    for(Shader *shader : shader_program->m_shaders){
        GLCALL(glAttachShader(shader_program->m_id,shader->m_id));
    }
    GLCALL(glLinkProgram(shader_program->m_id));
    GLCALL(glValidateProgram(shader_program->m_id));
}
void Renderer::deleteShader(ShaderProgram* shader_program){
    //TODO delete shaders and shaderProgram
    UNFINISHED;
}


// ----------------------------------- ShadowMap ----------------------------------

void Renderer::createShadowMap(unsigned int width, unsigned int height,
                               unsigned *fbo, unsigned *shadow_map_id) {
    GLCALL(glGenFramebuffers(1, fbo));

    GLCALL(glGenTextures(1, shadow_map_id));
    GLCALL(glBindTexture(GL_TEXTURE_2D, *shadow_map_id));
    GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0,
                        GL_DEPTH_COMPONENT, GL_FLOAT, nullptr));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, *fbo));
    GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                                  GL_TEXTURE_2D, *shadow_map_id, 0));

    GLCALL(glDrawBuffer(GL_NONE));
    GLCALL(glReadBuffer(GL_NONE));

    GLenum err = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (err != GL_FRAMEBUFFER_COMPLETE) {
        LOG_CRITICAL("%s has failed to create a framebuffer. error code: %i",
                     __func__, err);
    }

    GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void Renderer::writeShadowMap(unsigned fbo) {
    GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, fbo));
}

void Renderer::readShadowMap(unsigned texture_unit, unsigned shadow_map_id){
    GLCALL(glActiveTexture(texture_unit));
    GLCALL(glBindTexture(GL_TEXTURE_2D, shadow_map_id ));
}

void Renderer::deleteShadowMap(unsigned int fbo, unsigned int shadow_map_id){
    if(fbo) GLCALL(glDeleteFramebuffers(1, &fbo));
    if(shadow_map_id) GLCALL(glDeleteTextures(1, &shadow_map_id));
}
