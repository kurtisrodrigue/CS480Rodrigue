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
	void adjustGravity(float x,float y,float z);
	void Update(unsigned int dt);
	void Render();
        void Launch();

	// objects
	Object *m_ball; // basic sphere
	Object *m_box; // basic box
	Object *m_paddle_1;//paddle
	Object *m_paddle_2;//paddle
	Object *m_spring;//spring
	Object *m_cylinder1; // basic cylinder
	Object *m_cylinder2; // basic cylinder
	Object *m_cylinder3; // basic cylinder
	Object *m_plane; // basic plane to stop the ball from leaving the board
	Object *m_topWall; // part of surrounding wall
	Object *m_bottomWall;// part of surrounding wall
	Object *m_backBoard; // part of surrounding wall
	Object *m_deadWall;//part of surrounding wall
	Object *m_ricochetWall;//part of surrounding wall
	Object *m_containWall;//wall separating starting area from play area
	Object *m_backSplash;//
};

#endif //TUTORIAL_PHYSICS_H


