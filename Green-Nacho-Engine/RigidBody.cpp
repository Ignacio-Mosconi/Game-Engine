#include <PxPhysicsAPI.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "RigidBody.h"
#include "Transform.h"
#include "Collider.h"
#include "PhysicsManager.h"

namespace gn
{
	RigidBody::RigidBody() : Component(ComponentID::RigidBody),
		_rigidActor(NULL), _shape(NULL)
	{

	}

	RigidBody::~RigidBody()
	{

	}

	void RigidBody::start()
	{

	}

	void RigidBody::stop()
	{

	}

	void RigidBody::update()
	{
		physx::PxTransform pxTransform = _rigidActor->getGlobalPose();
		physx::PxVec3 pxPosition = pxTransform.p;

		_transform->setPosition(pxPosition.x, pxPosition.y, pxPosition.z);
	}

	void RigidBody::createRigidBody(Transform* transform, Collider* collider, bool isStatic)
	{
		_transform = transform;

		glm::vec3 position = _transform->getPosition();
		glm::vec3 rotation = _transform->getRotation();

		physx::PxQuat pxRotX(rotation.x, physx::PxVec3(1.0f, 0.0f, 0.0f));
		physx::PxQuat pxRotY(rotation.y, physx::PxVec3(0.0f, 1.0f, 0.0f));
		physx::PxQuat pxRotZ(rotation.z, physx::PxVec3(0.0f, 0.0f, 1.0f));
		
		physx::PxVec3 pxPosition(position.x, position.y, position.z);
		physx::PxQuat pxRotation(pxRotX * pxRotY * pxRotZ);

		physx::PxTransform pxTransform(pxPosition, pxRotation);
		physx::PxTransform relativePose(physx::PxQuat(physx::PxHalfPi, physx::PxVec3(0.0f, 0.0f, 1.0f)));;
		
		PhysicsManager* physicsManager = PhysicsManager::getInstance();
		
		physx::PxMaterial* pxMaterial = physicsManager->createPhysicsMaterial(0.5f, 0.5f, 1.0f);

		_rigidActor = physicsManager->createRigidActor(pxTransform, isStatic);

		physx::PxGeometry* geometry = collider->getGeometry();
		_shape = physx::PxRigidActorExt::createExclusiveShape(*_rigidActor, *geometry, *pxMaterial);
		_shape->setLocalPose(relativePose);

		physicsManager->addActor(_rigidActor);
	}
}