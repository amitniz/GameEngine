#version 330

in vec2 TexCoord;
in vec3 normal;
out vec4 color;

struct DirectionalLight{
    vec3 color;
    float ambient_intensity;
    float diffuse_intensity;
    vec3 direction;
};

uniform sampler2D u_sampler;
uniform DirectionalLight u_directional_light;

void main()
{

    vec4 ambient_color = vec4(u_directional_light.color,1.0f) * u_directional_light.ambient_intensity;
    float diffuse_factor = max(dot(normalize(normal),normalize(u_directional_light.direction)),0.0f);
    vec4 diffuse_color = vec4(u_directional_light.color,1.0f) * u_directional_light.diffuse_intensity * diffuse_factor; 
	color = texture(u_sampler,TexCoord) * (ambient_color+ diffuse_color);
}
