#include <PxPhysicsAPI.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "Scene Graph/RigidBody.h"
#include "Scene Graph/GameObject.h"
#include "Scene Graph/Transform.h"
#include "Scene Graph/Collider.h"
#include "Core/PhysicsManager.h"

namespace gn
{
	RigidBody::RigidBody(GameObject* gameObject) : Component(ComponentID::RigidBody, gameObject),
		_rigidActor(NULL), _shape(NULL), _material(NULL)
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

	void RigidBody::update(float deltaTime)
	{
		physx::PxTransform pxTransform = _rigidActor->getGlobalPose();
		physx::PxVec3 pxPosition = pxTransform.p;
		physx::PxQuat pxRotation = pxTransform.q;

		glm::vec3 transformPosition = glm::vec3(pxPosition.x, pxPosition.y, pxPosition.z);

		float pitch, yaw, roll;
		glm::vec4 rotQuat(pxRotation.x, pxRotation.y, pxRotation.z, pxRotation.w);
		
		Transform::convertToEulerAngles(rotQuat, pitch, yaw, roll);

		_transform->setPosition(transformPosition.x, transformPosition.y, transformPosition.z);
		_transform->setRotation(pitch, yaw, roll);
	}

	void RigidBody::createRigidBody(Collider* collider, bool isStatic, float mass, glm::vec3 colliderOffset)
	{
		_transform = _gameObject->getTransform();

		glm::vec3 position = _transform->getPosition();
		glm::vec3 rotation = _transform->getRotation();

		glm::vec4 rotQuat = Transform::convertToQuaternion(rotation.x, rotation.y, rotation.z);
	
		physx::PxVec3 pxPosition(position.x, position.y, position.z);
		physx::PxQuat pxRotation(rotQuat.x, rotQuat.y, rotQuat.z, rotQuat.w);

		physx::PxVec3 localOffset(colliderOffset.x, colliderOffset.y, colliderOffset.z);
		physx::PxQuat localRot(physx::PxHalfPi, physx::PxVec3(0.0f, 0.0f, 1.0f));
		physx::PxTransform pxTransform(pxPosition, pxRotation);
		physx::PxTransform relativePose(localOffset, localRot);
		
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