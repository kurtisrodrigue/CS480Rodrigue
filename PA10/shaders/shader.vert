#version 330

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec3 v_color;
layout (location = 2) in vec2 v_texture;
layout (location = 3) in vec3 v_normal;

out vec3 fN;
out vec3 fE;
out vec3 fL;

smooth out vec3 color;
smooth out vec2 pass_texture;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
out vec4 LightPosition;

void main(void)
{
    LightPosition = vec4(1,50,1,0);
    fN = v_normal;
    fE = v_position.xyz;
    fL = LightPosition.xyz;
    
    if(LightPosition.w != 0.0)
    {
        fL = LightPosition.xyz - v_position.xyz;
    }
    vec4 v = vec4(v_position, 1.0);
    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * v;
    color = v_color;
    pass_texture = v_texture;
}           
