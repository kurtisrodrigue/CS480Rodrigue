#ifndef TUTORIAL_PHYSICS_H
#define TUTORIAL_PHYSICS_H
#include "graphics_headers.h"
#include "object.h"

class Object;
class PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();
	// bullet things
	btBroadphaseInterface *m_broadphase;
	btDefaultCollisionConfiguration *m_configuration;
	btCollisionDispatcher *m_dispatcher;
	btSequentialImpulseConstraintSolver *m_solver;
	btDiscreteDynamicsWorld *m_dynamicsWorld;

	// functions
	void createObjects();
	void Update(unsigned int dt);
	void Render();

	// objects
	Object *m_board; // using triangle meshes
	Object *m_ball; // basic sphere
	Object *m_box; // basic box
	Object *m_cylinder; // basic cylinder
	Object *m_plane; // basic plane to stop the ball from leaving the board


};

#endif //TUTORIAL_PHYSICS_H


