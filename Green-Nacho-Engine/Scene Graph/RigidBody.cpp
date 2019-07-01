#include <PxPhysicsAPI.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "Scene Graph/RigidBody.h"
#include "Scene Graph/Transform.h"
#include "Scene Graph/Collider.h"
#include "Core/PhysicsManager.h"

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
		disposeRigidBody();
	}

	void RigidBody::update()
	{
		physx::PxTransform pxTransform = _rigidActor->getGlobalPose();
		physx::PxVec3 pxPosition = pxTransform.p;
		physx::PxQuat pxRotation = pxTransform.q;

		float pitch, yaw, roll;
		glm::vec4 rotQuat(pxRotation.x, pxRotation.y, pxRotation.z, pxRotation.w);
		
		Transform::convertToEulerAngles(rotQuat, pitch, yaw, roll);

		_transform->setPosition(pxPosition.x, pxPosition.y, pxPosition.z);
		_transform->setRotation(pitch, yaw, roll);
	}

	void RigidBody::createRigidBody(Transform* transform, Collider* collider, bool isStatic, float mass)
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

		_rigidActor = physicsManager->createRigidActor(pxTransform, isStatic);
		_material = physicsManager->createPhysicsMaterial(0.5f, 0.5f, 1.0f);
		_shape = physx::PxRigidActorExt::createExclusiveShape(*_rigidActor, *geometry, *_material);
		
		_shape->setLocalPose(relativePose);

		if (!isStatic)
		{
			physx::PxRigidDynamic* rigidDynamic = (physx::PxRigidDynamic*)_rigidActor;
			rigidDynamic->setMassSpaceInertiaTensor(physx::PxVec3(1.0f, 1.0f, 1.0f));
			physx::PxRigidBodyExt::setMassAndUpdateInertia(*rigidDynamic, (physx::PxReal)mass);
		}

		physicsManager->addActor(_rigidActor);
	}

	void RigidBody::disposeRigidBody()
	{
		if (_rigidActor)
		{
			if (_material)
				_material->release();
			if (_shape)
				_rigidActor->detachShape(*_shape);
			PhysicsManager::getInstance()->removeActor(_rigidActor);
			_rigidActor->release();
		}
	}
}