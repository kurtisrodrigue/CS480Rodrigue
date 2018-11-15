#version 330
smooth in vec3 color;
smooth in vec2 pass_texture;
in vec3 fN;
in vec3 fE;
in vec3 fL;
in vec4 LightPosition;

uniform vec4 AmbientProduct;
uniform vec4 DiffuseProduct;
uniform vec4 SpecularProduct;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform float Shininess;

uniform sampler2D sampler;
out vec4 frag_color;
void main(void)
{
    vec3 N = normalize(fN);
    vec3 E = normalize(fE);
    vec3 L = normalize(fL);
    vec3 H = normalize(L+E);
    vec4 ambient = AmbientProduct;
    
    float kD = max(dot(L,N), 0.0);
    vec4 diffuse = kD * DiffuseProduct;
    
    float Ks = pow(max(dot(N,H), 0.0), Shininess);
    vec4 specular = Ks * SpecularProduct;
    
    if(dot(L,N) < 0.0)
    {
        specular = vec4( 0.0 , 0.0 , 0.0 , 0.0 );
    }
    frag_color = texture(sampler, pass_texture) * (ambient + diffuse + specular);
    frag_color.a = 1.0;
}           
