#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"
class Planet;

class Object
{
    friend class Engine;
    friend class Graphics;
  public:
    Object();
    ~Object();
    virtual void Update(unsigned int dt);
    virtual void Render();

    glm::mat4 GetModel();

  protected:
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

class Moon : public Object
{
public:
    friend class Planet;
    Moon(Planet*);
    virtual void Update(unsigned int dt);
    virtual void Render();
    Planet* m_planet;
};

class Planet : public Object
{
public:
    friend class Moon;
    Planet();
    virtual void Update(unsigned int dt);
    std::vector<Moon*> m_moons;
};

#endif /* OBJECT_H */
