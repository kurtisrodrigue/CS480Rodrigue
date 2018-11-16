#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"
class Planet;
class Moon;

class Object
{
    friend class Engine;
    friend class Graphics;
    friend class Rings;
  public:
    Object();
    Object(std::string);
    Object(std::string, std::string);
    ~Object();
    virtual void Update(unsigned int dt);
    virtual void Render();
    void ChangeDirection();
    glm::mat4 Scale();

    glm::mat4 GetModel();
    
    void LoadOBJ(const char* obj, const char* tex);


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

	double m_orbitSpeed;

    double m_size;


	std::string obj_file;
	std::string texture_file;
};

class Sun : public Object
{
public:
	Sun(std::string);
	virtual void Update(unsigned int dt);
	void refactorOrbits();
	std::vector<Planet*> m_planets;
	std::vector<Moon*> m_moons;
	float simulationSpeed;
};

class Moon : public Object
{
public:
    friend class Planet;
    friend class Sun;
    Moon(Planet*, int);
    Moon(Planet*, int, std::string, std::string);
    virtual void Update(unsigned int dt);
    virtual void Render();
    Planet* m_planet;
    float m_size;
    int moon_number;
};

class Rings : public Moon
{
public:
	Rings(Planet*, int);
	virtual void Update(unsigned int dt);
};

class Planet : public Object
{
public:

    friend class Moon;
    friend class Sun;

	Sun* m_sun;
    Planet(std::string);
    virtual void Update(unsigned int dt);

};

class Mercury: public Planet
{
public:
	Mercury(std::string);
};

class Venus: public Planet
{
public:
	Venus(std::string);
};

class Earth: public Planet
{
public:
	Earth(std::string);
};

class Mars: public Planet
{
public:
	Mars(std::string);
};

class Jupiter: public Planet
{
public:
	Jupiter(std::string);
};

class Saturn: public Planet
{
public:
	Saturn(std::string);
};

class Uranus: public Planet
{
public:
	Uranus(std::string);
};

class Neptune: public Planet
{
public:
	Neptune(std::string);
};

class Pluto : public Planet
{
public:
	Pluto(std::string);
};

#endif /* OBJECT_H */
