#pragma once
#include <btBulletDynamicsCommon.h>
#include "Transform.h"

// Ref http://www.cs.kent.edu/~ruttan/GameEngines/lectures/Bullet_User_Manual
class RigidBody;

class Physics
{
private:
	static Physics* m_instance;
	btConstraintSolver* m_solver = new btSequentialImpulseConstraintSolver();
	btCollisionConfiguration* m_collisionConfig = new btDefaultCollisionConfiguration();
	btDispatcher* m_dispatcher = new btCollisionDispatcher(m_collisionConfig);
	btBroadphaseInterface* m_broadphase = new btDbvtBroadphase();
	btDynamicsWorld* m_world = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfig);
	std::vector<RigidBody*> m_rbodies;

	Physics();

	void Init();
public:
	static Physics* GetInstance();
	inline btDynamicsWorld* GetWorld() { return GetInstance()->m_world; };
	void AddRigidbody(RigidBody* r);
	void PreUpdate();
	void Update(float deltaTime);
	void Quit();
	bool Collision3D(btCollisionObject* obj1, int id1, int index1, btCollisionObject* obj2, int id2, int index2);
	static btTransform ConvertTransformToBtTransform(Transform t);
};

