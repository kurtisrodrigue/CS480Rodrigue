#ifndef SHADER_H
#define SHADER_H

#include <vector>

#include "graphics_headers.h"

class Shader
{
  public:
    Shader();
    Shader(std::string frag, std::string vert);
    ~Shader();
    bool Initialize();
    void Enable();
    bool AddShader(GLenum ShaderType);
    bool Finalize();
    GLint GetUniformLocation(const char* pUniformName);

  private:
    GLuint m_shaderProg;    
    std::vector<GLuint> m_shaderObjList;

    std::string m_fragmentShader;
    std::string m_vertexShader;
};

#endif  /* SHADER_H */
