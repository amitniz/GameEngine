#version 330

in vec2 TexCoord;
in vec3 normal;
in vec3 position;
out vec4 color;

struct DirectionalLight{
    vec3 color;
    float ambient_intensity;
    float diffuse_intensity;
    float shininess;
    vec3 direction;
};

uniform sampler2D u_sampler;
uniform DirectionalLight u_directional_light;
uniform vec3 u_camera_position;


void main()
{
    
    vec4 ambient_color = vec4(u_directional_light.color,1.0f) * u_directional_light.ambient_intensity;

    float diffuse_factor = max(dot(normalize(normal), normalize(u_directional_light.direction)),0.0f);
    vec4 diffuse_color = vec4(u_directional_light.color * u_directional_light.diffuse_intensity * diffuse_factor,1.0f); 
    vec4 specular_color = vec4(0.0f,0.0f,0.0f,0.0f);

    if(diffuse_factor > 0.0f){

      vec3 frag_to_camera = normalize(position- u_camera_position);
      vec3 light_reflection = normalize(reflect(u_directional_light.direction,normalize(normal)));

      float specular_factor = dot(frag_to_camera,light_reflection); 
      if(specular_factor > 0.0f){
        specular_factor = pow(specular_factor,50.0f);
        specular_color = vec4(u_directional_light.color * specular_factor *0.9,1.0f); 
      } 
    }
    color = texture(u_sampler,TexCoord) * ( ambient_color +diffuse_color+ specular_color);
}
