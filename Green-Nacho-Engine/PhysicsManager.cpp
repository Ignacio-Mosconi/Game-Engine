#include <PxPhysicsAPI.h>
#include "PhysicsManager.h"

namespace gn
{
	PhysicsManager* PhysicsManager::_instance = NULL;

	PhysicsManager::PhysicsManager()
	{

	}

	PhysicsManager::~PhysicsManager()
	{

	}

	bool PhysicsManager::start()
	{
		static physx::PxDefaultAllocator defaultAllocator;
		static physx::PxDefaultErrorCallback defaultErrorCallback;

		_foundation = PxCreateFoundation(PX_PHYSICS_VERSION, defaultAllocator, defaultErrorCallback);
		if (!_foundation)
			std::cerr << "Failed to initilaize the PxFoundation object." << std::endl;

		_physics = PxCreatePhysics(PX_PHYSICS_VERSION, *_foundation, physx::PxTolerancesScale());
		if (!_physics)
			std::cerr << "Failed to initilaize the PxPhysics object." << std::endl;

		return (_physics != NULL);
	}

	void PhysicsManager::stop()
	{
		if (_physics)
			_physics->release();
		if (_foundation)
			_foundation->release();
	}

	PhysicsManager* PhysicsManager::getInstance()
	{
		if (!_instance)
			_instance = new PhysicsManager();

		return _instance;
	}

	void PhysicsManager::deleteInstance()
	{
		if (_instance)
			delete _instance;
	}
}