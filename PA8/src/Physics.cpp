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

PhysicsEngine::~PhysicsEngine()
{
	delete m_broadphase;
	delete m_configuration;
	delete m_dispatcher;
	delete m_solver;
	delete m_dynamicsWorld;
}

void PhysicsEngine::Update(unsigned int dt)
{
	m_board->Update(dt);
	m_box->Update(dt);
	m_ball->Update(dt);
	m_cylinder->Update(dt);
}

void PhysicsEngine::createObjects()
{

	//BOARD
	m_board = new Object("../assets/board.obj" , "../assets/woodtex.jpeg",3.0f);
	m_board->m_physics = this;

	btVector3 triArray[3];
	btTriangleMesh *board = new btTriangleMesh;
	for(int i = 0; i < m_board->Indices.size(); i += 3)
	{
		triArray[0] = btVector3(m_board->Vertices[m_board->Indices[i]].vertex.x,
		                        m_board->Vertices[m_board->Indices[i]].vertex.y,
		                        m_board->Vertices[m_board->Indices[i]].vertex.z);

		triArray[1] = btVector3(m_board->Vertices[m_board->Indices[i + 1]].vertex.x,
		                        m_board->Vertices[m_board->Indices[i + 1]].vertex.y,
		                        m_board->Vertices[m_board->Indices[i + 1]].vertex.z);

		triArray[2] = btVector3(m_board->Vertices[m_board->Indices[i + 2]].vertex.x,
		                        m_board->Vertices[m_board->Indices[i + 2]].vertex.y,
		                        m_board->Vertices[m_board->Indices[i + 2]].vertex.z);

		board->addTriangle(triArray[0], triArray[1], triArray[2]);
	}
	m_board->m_shape = new btBvhTriangleMeshShape(board, true);

	btDefaultMotionState *shapeMotionState = NULL;

	shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),
															btVector3(0, 0, 0)));
	btScalar mass(0);
	btVector3 inertia(1, 1, 1);
	m_board->m_shape->calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, shapeMotionState, m_board->m_shape, inertia);
	m_board->m_rigidbody = new btRigidBody(shapeRigidBodyCI);
	m_dynamicsWorld->addRigidBody(m_board->m_rigidbody, 1 , 1);
	m_board->m_rigidbody->setGravity(btVector3(0,0,0));


	// BOX -----------------------------------------------------------
	m_box = new Object("../assets/box.obj" , "../assets/woodtex.jpeg",0.5f);
	m_box->m_physics = this;
	m_box->m_shape = new btBoxShape(btVector3(0,3,0));
	shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),
	                                                        btVector3(0, 3, 0)));
	mass = 0;
	m_box->m_shape->calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI3(mass, shapeMotionState, m_box->m_shape, inertia);
	m_box->m_rigidbody = new btRigidBody(shapeRigidBodyCI3);
	m_dynamicsWorld->addRigidBody(m_box->m_rigidbody, 1 , 1);

	// BALL -----------------------------------------------------------
	m_ball = new Object("../assets/sphere.obj" , "../assets/metal.jpg",0.2f);
	m_ball->m_physics = this;
	m_ball->m_shape = new btBoxShape(btVector3(0,3,0));
	shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),
	                                                        btVector3(3, 3, 0)));
	mass = 1;
	m_ball->m_shape->calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI2(mass, shapeMotionState, m_ball->m_shape, inertia);
	m_ball->m_rigidbody = new btRigidBody(shapeRigidBodyCI2);
	m_dynamicsWorld->addRigidBody(m_ball->m_rigidbody, 1 , 1);

	// Cylinder -----------------------------------------------------------
	m_cylinder = new Object("../assets/cylinder.obj" , "../assets/woodtex.jpeg",0.5f);
	m_cylinder->m_physics = this;
	m_cylinder->m_shape = new btCylinderShape(btVector3(0,3,0));
	shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),
	                                                        btVector3(-3, 3, 0)));
	mass = 0;
	m_cylinder->m_shape->calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI4(mass, shapeMotionState, m_cylinder->m_shape, inertia);
	m_cylinder->m_rigidbody = new btRigidBody(shapeRigidBodyCI4);
	m_dynamicsWorld->addRigidBody(m_cylinder->m_rigidbody, 1 , 1);


}

