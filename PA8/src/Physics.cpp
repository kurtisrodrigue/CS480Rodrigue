#include "Physics.h"

PhysicsEngine::PhysicsEngine() {
	m_broadphase = new btDbvtBroadphase();
	m_configuration = new btDefaultCollisionConfiguration();
	m_dispatcher = new btCollisionDispatcher(m_configuration);
	m_solver = new btSequentialImpulseConstraintSolver();
	m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_configuration);
	m_dynamicsWorld->setGravity(btVector3(-1, -9.81, -1));
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
	m_plane->Update(dt);
	m_box->Update(dt);
	m_ball->Update(dt);
//	m_cylinder->Update(dt);
}

void PhysicsEngine::Render()
{
	m_plane->Render();
	m_box->Render();
}

void PhysicsEngine::adjustGravity(float x,float y,float z)
{
	m_dynamicsWorld->setGravity(btVector3(x,y,z));
}

void PhysicsEngine::createObjects()
{
/*	//BOARD
	m_plane = new Object("../assets/board5.obj" , "../assets/woodtex.jpeg",1.0f);
	m_plane->m_physics = this;

	btVector3 triArray[3];
	btTriangleMesh *board = new btTriangleMesh;
	for(int i = 0; i < m_plane->Indices.size(); i += 3)
	{
		triArray[0] = btVector3(m_plane->Vertices[m_plane->Indices[i]].vertex.x,
		                        m_plane->Vertices[m_plane->Indices[i]].vertex.y,
		                        m_plane->Vertices[m_plane->Indices[i]].vertex.z);

		triArray[1] = btVector3(m_plane->Vertices[m_plane->Indices[i + 1]].vertex.x,
		                        m_plane->Vertices[m_plane->Indices[i + 1]].vertex.y,
		                        m_plane->Vertices[m_plane->Indices[i + 1]].vertex.z);

		triArray[2] = btVector3(m_plane->Vertices[m_plane->Indices[i + 2]].vertex.x,
		                        m_plane->Vertices[m_plane->Indices[i + 2]].vertex.y,
		                        m_plane->Vertices[m_plane->Indices[i + 2]].vertex.z);
		                        
		board->addTriangle(triArray[0], triArray[1], triArray[2]);
	}
	m_plane->m_shape = new btBvhTriangleMeshShape(board, true);

	btDefaultMotionState *shapeMotionState = NULL;

	shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),
															btVector3(0, 0, 0)));
	
	btScalar mass(0);
	btVector3 inertia(1, 1, 1);
	m_plane->m_shape->calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, shapeMotionState, m_plane->m_shape, inertia);
	m_plane->m_rigidbody = new btRigidBody(shapeRigidBodyCI);
	m_dynamicsWorld->addRigidBody(m_plane->m_rigidbody, 1 , 1);
	m_plane->m_rigidbody->setGravity(btVector3(0,0,0)); */
	
	btDefaultMotionState *shapeMotionState = NULL;

	shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),
															btVector3(0, 0, 0)));
	
	btScalar mass(0);
	btVector3 inertia(1, 1, 1);
	
	//Board ------------------------------------------------------------------------------------
	m_plane = new Object("../assets/board5.obj","../assets/woodtex.jpeg",1.0f);
	m_plane->m_physics = this;
	m_plane->m_shape = new btBoxShape(btVector3(100,1,100));
	shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
	
	mass = 0;
	m_plane->m_shape->calculateLocalInertia(mass,inertia);
	btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, shapeMotionState, m_plane->m_shape, inertia);
	m_plane->m_rigidbody = new btRigidBody(shapeRigidBodyCI);
	m_dynamicsWorld->addRigidBody(m_plane->m_rigidbody,1,1);
	
	//bottom
	m_deadWall = new Object();
	m_deadWall->m_physics = this;
	m_deadWall->m_shape = new btBoxShape(btVector3(1,3,100));
	shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(8.3,-1,0)));
	mass = 0;
	m_deadWall->m_shape->calculateLocalInertia(mass,inertia);
	btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI5(mass, shapeMotionState, m_deadWall->m_shape, inertia);
	m_deadWall->m_rigidbody = new btRigidBody(shapeRigidBodyCI5);
	m_dynamicsWorld->addRigidBody(m_deadWall->m_rigidbody,1,1);
	
	//right
	m_topWall = new Object();
	m_topWall->m_physics = this;
	m_topWall->m_shape = new btBoxShape(btVector3(100,3,1));
	shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,-3.4)));
	mass = 0;
	m_topWall->m_shape->calculateLocalInertia(mass,inertia);
	btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI6(mass, shapeMotionState, m_topWall->m_shape, inertia);
	m_topWall->m_rigidbody = new btRigidBody(shapeRigidBodyCI6);
	m_dynamicsWorld->addRigidBody(m_topWall->m_rigidbody,1,1);
	
	//left
	m_bottomWall = new Object();
	m_bottomWall->m_physics = this;
	m_bottomWall->m_shape = new btBoxShape(btVector3(100,3,1));
	shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,3.6)));
	mass = 0;
	m_bottomWall->m_shape->calculateLocalInertia(mass,inertia);
	btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI7(mass, shapeMotionState, m_bottomWall->m_shape, inertia);
	m_bottomWall->m_rigidbody = new btRigidBody(shapeRigidBodyCI7);
	m_dynamicsWorld->addRigidBody(m_bottomWall->m_rigidbody,1,1);
	
	//top
	m_backBoard = new Object();
	m_backBoard->m_physics = this;
	m_backBoard->m_shape = new btBoxShape(btVector3(1,3,100));
	shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(-4,-1,0)));
	mass = 0;
	m_backBoard->m_shape->calculateLocalInertia(mass,inertia);
	btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI8(mass, shapeMotionState, m_backBoard->m_shape, inertia);
	m_backBoard->m_rigidbody = new btRigidBody(shapeRigidBodyCI8);
	m_dynamicsWorld->addRigidBody(m_backBoard->m_rigidbody,1,1);
	
	//retaining wall
	m_containWall = new Object();
	m_containWall->m_physics = this;
	m_containWall->m_shape = new btBoxShape(btVector3(30,3,1));
	shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(29.5,-1,-3)));
	mass = 0;
	m_containWall->m_shape->calculateLocalInertia(mass,inertia);
	btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI9(mass, shapeMotionState, m_containWall->m_shape, inertia);
	m_containWall->m_rigidbody = new btRigidBody(shapeRigidBodyCI9);
	m_dynamicsWorld->addRigidBody(m_containWall->m_rigidbody,1,1);
	
	
	
	// BALL ----------------------------------------------------------------------------------------------------
	m_ball = new Object("../assets/sphere.obj" , "../assets/metal.jpg",0.1f);
	m_ball->m_physics = this;
	m_ball->m_shape = new btSphereShape(btScalar(1));
	shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),
	                                                        btVector3(5, 1,-.5)));
	mass = 1;
	m_ball->m_shape->calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI2(mass, shapeMotionState, m_ball->m_shape, inertia);
	m_ball->m_rigidbody = new btRigidBody(shapeRigidBodyCI2);
	m_dynamicsWorld->addRigidBody(m_ball->m_rigidbody, 1 , 1);

	std::cout<<"sucks to suck"<<std::endl;
	// Cylinder1 --------------------------------------------------------------------------------------------------
	m_cylinder1 = new Object("../assets/cylinder2.obj" , "../assets/Iroko_wood.jpg",0.2f);
	m_cylinder1->m_physics = this;
	m_cylinder1->m_shape = new btCylinderShape(btVector3(0,3,0));
	shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),
	                                                        btVector3(0, 0, 0)));
	mass = 0;
	m_cylinder1->m_shape->calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI3(mass, shapeMotionState, m_cylinder1->m_shape, inertia);
	m_cylinder1->m_rigidbody = new btRigidBody(shapeRigidBodyCI3);
	m_dynamicsWorld->addRigidBody(m_cylinder1->m_rigidbody, 1 , 1);
	
	std::cout<<"sucks to suck"<<std::endl;
	// Cylinder2 --------------------------------------------------------------------------------------------------
	m_cylinder2 = new Object("../assets/cylinder2.obj" , "../assets/Iroko_wood.jpg",0.2f);
	m_cylinder2->m_physics = this;
	m_cylinder2->m_shape = new btCylinderShape(btVector3(0,3,0));
	shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),
	                                                        btVector3(-.5, 10, 10)));
	mass = 0;
	m_cylinder2->m_shape->calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI4(mass, shapeMotionState, m_cylinder2->m_shape, inertia);
	m_cylinder2->m_rigidbody = new btRigidBody(shapeRigidBodyCI4);
	m_dynamicsWorld->addRigidBody(m_cylinder2->m_rigidbody, 1 , 1);
	
	std::cout<<"sucks to suck"<<std::endl;
	// Cylinder3 --------------------------------------------------------------------------------------------------
	m_cylinder3 = new Object("../assets/cylinder2.obj" , "../assets/Iroko_wood.jpg",0.2f);
	m_cylinder3->m_physics = this;
	m_cylinder3->m_shape = new btCylinderShape(btVector3(0,3,0));
	shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),
	                                                        btVector3(-.5, 10, 10)));
	mass = 0;
	m_cylinder3->m_shape->calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI10(mass, shapeMotionState, m_cylinder3->m_shape, inertia);
	m_cylinder3->m_rigidbody = new btRigidBody(shapeRigidBodyCI10);
	m_dynamicsWorld->addRigidBody(m_cylinder3->m_rigidbody, 1 , 1);
	
	
/*	// Spring -------------------------------------------------------------
	m_spring = new Object("../assests/spring2.obj","../assets/metal.jpg", .1f);
	m_spring->m_physics = this;
	m_spring->m_shape = new btBoxShape(btVector3(0,3,0));
	shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(5,0,-1.5)));
	
	mass = 0;
	m_spring->m_shape->calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI5(mass, shapeMotionState, m_spring->m_shape, inertia);
	m_spring->m_rigidbody = new btRigidBody(shapeRigidBodyCI5);
	m_dynamicsWorld->addRigidBody(m_spring->m_rigidbody,1,1);*/

}

