#version 330

layout (location = 0) in vec3 vertex_pos;
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 vertex_normal;

// outputs
out vec2 texture_coords;
out vec3 normal;
out vec3 position;
out vec4 directional_light_space_pos;

// uniforms
uniform mat4 u_model;
uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_directional_light_transform;

mat3 normal_matrix(mat4 model){
  return mat3(transpose(inverse(model)));
}

void main()
{
    texture_coords = tex;
    position = (u_model * vec4(vertex_pos,1.0)).xyz;
    normal = normal_matrix(u_model) * vertex_normal;
    directional_light_space_pos = u_directional_light_transform * u_model * vec4(vertex_pos,1.0);

    gl_Position =  u_projection * u_view * u_model * vec4(vertex_pos, 1.0);
}
