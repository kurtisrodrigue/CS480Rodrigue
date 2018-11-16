#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"

class Object
{
    friend class Engine;
  public:
    Object();
    ~Object();
    void Update(unsigned int dt);
    void Render();
    void LoadOBJ(char* obj);

    glm::mat4 GetModel();

  private:
    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    float angle;
    float orbit_angle;
    float orbit_radius;
    bool orbit_direction;
    bool spin_direction;
};

#endif /* OBJECT_H */
