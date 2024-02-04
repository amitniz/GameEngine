#version 330
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 norm;

out vec4 vCol;
out vec2 TexCoord;
out vec3 normal;
out vec3 position;

uniform mat4 u_model;
uniform mat4 u_projection;
uniform mat4 u_view;

void main()
{
	gl_Position =  u_projection * u_view * u_model * vec4(pos, 1.0);
    TexCoord = tex;
    position = (u_model * vec4(pos,1.0)).xyz;
    normal = mat3(transpose(inverse(u_model))) * norm;
}
