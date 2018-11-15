#version 330

in vec4 color;
smooth in vec2 pass_texture;

uniform sampler2D sampler;

out vec4 frag_color;

void main(void)
{
    frag_color = color * texture(sampler, pass_texture);
    frag_color.a = 1.0;
}
