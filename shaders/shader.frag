#version 330

in vec2 texture_coords;
in vec3 normal;
in vec3 position;
in vec4 directional_light_space_pos;

out vec4 color;

struct Material{
  float shininess;
  float specular_intensity;
};

struct DirectionalLight{
    vec3 color;
    float ambient_intensity;
    float diffuse_intensity;
    float shininess;
    vec3 direction;
};

uniform sampler2D u_sampler;
uniform sampler2D u_directional_shadow_map;

uniform DirectionalLight u_directional_light;
uniform vec3 u_camera_position;

vec4 calculateAmbientLight(vec3 color, float intensity){
    return vec4(color,1.0f) * intensity;
}

vec4 calculateDiffuseLight(vec3 light_direction, vec3 frag_normal, vec3 color, float intensity){
    float diffuse_factor = max(dot(normalize(frag_normal), normalize(light_direction)),0.0f);
    if (diffuse_factor > 0.0f){
      return vec4(color * intensity * diffuse_factor,1.0f); 
    } 
    return vec4(0.0f);
}

void main()
{
    
    float diffuse_factor = max(dot(normalize(normal), normalize(u_directional_light.direction)),0.0f);
    vec4 specular_color = vec4(0.0f,0.0f,0.0f,0.0f);

    if(diffuse_factor > 0.0f){

      vec3 frag_to_camera = normalize(position - u_camera_position);
      vec3 light_reflection = normalize(reflect(u_directional_light.direction,normal));

      float specular_factor = dot(frag_to_camera,light_reflection); 
      if(specular_factor > 0.0f){
        specular_factor = pow(specular_factor,50.0f);
        specular_color = vec4(u_directional_light.color * specular_factor,1.0f); 
      } 
    }

    vec4 ambient_light = calculateAmbientLight(u_directional_light.color, u_directional_light.ambient_intensity);
    vec4 diffuse_light = calculateDiffuseLight(u_directional_light.direction, normal,u_directional_light.color,u_directional_light.diffuse_intensity);

    color = texture(u_sampler,texture_coords) * ( ambient_light + diffuse_light+ specular_color);

}
