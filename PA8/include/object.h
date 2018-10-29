#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"

class Object
{
  public:
    Object();
    ~Object();
    void Update(unsigned int dt);
    void Render();
	void LoadOBJ(const char* obj, const char* tex);


	glm::mat4 GetModel();

  private:
    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

	GLuint texture;

	const aiScene* m_aiscene;

	Magick::Blob m_blob;

    float angle;
    float orbit_angle;
};

#endif /* OBJECT_H */
