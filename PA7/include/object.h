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
    
    void LoadOBJ(const char* obj);


  protected:
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
    float orbit_radius;
    bool orbit_direction;
    bool spin_direction;


	std::string obj_file;
	std::string texture_file;
};

class Sun : public Object
{
	Sun();
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

class Mercury: public Planet
{
	Mercury();
};

class Venus: public Planet
{
	Venus();
};

class Earth: public Planet
{
	Earth();
};

class Mars: public Planet
{
	Mars();
};

class Jupiter: public Planet
{
	Jupiter();
};

class Saturn: public Planet
{
	Saturn();
};

class Uranus: public Planet
{
	Uranus();
};

class Neptune: public Planet
{
	Neptune();
};

class Pluto : public Planet
{
	Pluto();
};

#endif /* OBJECT_H */
