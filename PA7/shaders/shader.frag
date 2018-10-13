#version 330
smooth in vec3 color;
smooth in vec2 pass_texture;
uniform sampler2D sampler;
out vec4 frag_color;
void main(void)
{
    frag_color = texture(sampler, pass_texture);
}           
