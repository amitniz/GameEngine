#version 330

in vec4 vCol;
in vec2 TexCoord;
out vec4 colour;
uniform sampler2D sampler;

void main()
{
	colour = texture(sampler,TexCoord);
}
