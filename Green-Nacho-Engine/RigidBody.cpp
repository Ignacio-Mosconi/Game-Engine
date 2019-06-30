#include <PxPhysicsAPI.h>
#include <glm\vec3.hpp>
#include <glm\vec4.hpp>
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
		physx::PxQuat pxRotation = pxTransform.q;

		float pitch, yaw, roll;
		glm::vec4 rotQuat(pxRotation.x, pxRotation.y, pxRotation.z, pxRotation.w);
		
		Transform::convertToEulerAngles(rotQuat, pitch, yaw, roll);

		//_transform->setPosition(pxPosition.x, pxPosition.y, pxPosition.z);
		_transform->setRotation(pitch, yaw, roll);
	}

	void RigidBody::createRigidBody(Transform* transform, Collider* collider, bool isStatic)
	{
		_transform = transform;

		glm::vec3 position = _transform->getPosition();
		glm::vec3 rotation = _transform->getRotation();

		glm::vec4 rotQuat = Transform::convertToQuaternion(rotation.x, rotation.y, rotation.z);
	
		physx::PxVec3 pxPosition(position.x, position.y, position.z);
		physx::PxQuat pxRotation(rotQuat.x, rotQuat.y, rotQuat.z, rotQuat.w);

		physx::PxTransform pxTransform(pxPosition, pxRotation);
		physx::PxTransform relativePose(physx::PxQuat(physx::PxHalfPi, physx::PxVec3(0.0f, 0.0f, 1.0f)));;
		
		PhysicsManager* physicsManager = PhysicsManager::getInstance();
		
		physx::PxGeometry* geometry = collider->getGeometry();
		physx::PxMaterial* pxMaterial = physicsManager->createPhysicsMaterial(0.5f, 0.5f, 1.0f);

		_rigidActor = physicsManager->createRigidActor(pxTransform, isStatic);
		_shape = physx::PxRigidActorExt::createExclusiveShape(*_rigidActor, *geometry, *pxMaterial);
		_shape->setLocalPose(relativePose);

		physicsManager->addActor(_rigidActor);
	}
}