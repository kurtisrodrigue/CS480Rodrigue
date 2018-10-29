#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"
#include "Physics.h"

class PhysicsEngine;
class Object
{
	friend class PhysicsEngine;
  public:
    Object();
    Object(const char* obj, const char* tex);
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

	PhysicsEngine *m_physics;

	btCollisionShape *m_shape;
	btRigidBody *m_rigidbody;

    float angle;
    float orbit_angle;
};

#endif /* OBJECT_H */
