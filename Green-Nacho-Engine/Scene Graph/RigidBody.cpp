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
	RigidBody::RigidBody(GameObject* gameObject) : Component(ComponentID::RIGID_BODY, gameObject),
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

		glm::vec3 pos = glm::vec3(pxPosition.x, pxPosition.y, pxPosition.z);
		glm::vec4 rotQuat(pxRotation.x, pxRotation.y, pxRotation.z, pxRotation.w);

		_transform->setPosition(pos.x, pos.y, pos.z);
		_transform->changeRotationMatrix(rotQuat);
	}

	void RigidBody::createRigidBody(Collider* collider, bool isStatic, float mass, glm::vec3 colliderOffset)
	{
		_transform = _gameObject->getTransform();
		_isStatic = isStatic;

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

		_rigidActor = physicsManager->createRigidActor(pxTransform, _isStatic);
		_material = physicsManager->createPhysicsMaterial(0.5f, 0.5f, 1.0f);
		_shape = physx::PxRigidActorExt::createExclusiveShape(*_rigidActor, *geometry, *_material);
		
		_shape->setLocalPose(relativePose);

		if (!_isStatic)
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

	void RigidBody::addForce(glm::vec3 force, ForceMode forceMode)
	{
		if (_isStatic)
		{
			std::cout << "WARNING: Attempting to add force to a rigid static body." << std::endl;
			return;
		}
		physx::PxRigidDynamic* rigidDynamic = (physx::PxRigidDynamic*)_rigidActor;
		physx::PxVec3 pxForce(force.x, force.y, force.z);

		rigidDynamic->addForce(pxForce, (physx::PxForceMode::Enum)forceMode);
	}

	void RigidBody::addTorque(glm::vec3 torque, ForceMode forceMode)
	{
		if (_isStatic)
		{
			std::cout << "WARNING: Attempting to add torque to a rigid static body." << std::endl;
			return;
		}
		physx::PxRigidDynamic* rigidDynamic = (physx::PxRigidDynamic*)_rigidActor;
		physx::PxVec3 pxTorque(torque.x, torque.y, torque.z);

		rigidDynamic->addTorque(pxTorque, (physx::PxForceMode::Enum)forceMode);
	}
	
	void RigidBody::clearTorque(ForceMode forceMode)
	{
		if (_isStatic)
		{
			std::cout << "WARNING: Attempting to clear force from a rigid static body." << std::endl;
			return;
		}
		physx::PxRigidDynamic* rigidDynamic = (physx::PxRigidDynamic*)_rigidActor;

		rigidDynamic->clearTorque((physx::PxForceMode::Enum)forceMode);
	}
}