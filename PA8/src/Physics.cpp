#include "Physics.h"

PhysicsEngine::PhysicsEngine() {
	m_broadphase = new btDbvtBroadphase();
	m_configuration = new btDefaultCollisionConfiguration();
	m_dispatcher = new btCollisionDispatcher(m_configuration);
	m_solver = new btSequentialImpulseConstraintSolver();
	m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_configuration);
	m_dynamicsWorld->setGravity(btVector3(0, -9.81, 0));
	createObjects();
}

void PhysicsEngine::createObjects() {
	m_board = new Object("../assets/sphere.obj" , "../assets/woodtex.jpeg");
	m_board->m_physics = this;
	// create/call Object function to do instructions on slide 14
	// the board will have to use the special triangle mesh loading
	// boo-yah EC

	// load rest of the objects

}

