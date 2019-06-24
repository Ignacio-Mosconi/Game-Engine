#include <PxPhysicsAPI.h>
#include "PhysicsManager.h"

namespace gn
{
	PhysicsManager* PhysicsManager::_instance = NULL;

	PhysicsManager::PhysicsManager() : _foundation(NULL), _physics(NULL), _scene(NULL), 
		_sceneDesc(NULL)
	{

	}

	PhysicsManager::~PhysicsManager()
	{

	}

	bool PhysicsManager::start(glm::vec3 gravity)
	{
		static physx::PxDefaultAllocator defaultAllocator;
		static physx::PxDefaultErrorCallback defaultErrorCallback;

		_foundation = PxCreateFoundation(PX_PHYSICS_VERSION, defaultAllocator, defaultErrorCallback);
		if (!_foundation)
			std::cerr << "Failed to initilaize the PxFoundation object." << std::endl;

		_physics = PxCreatePhysics(PX_PHYSICS_VERSION, *_foundation, physx::PxTolerancesScale());
		if (!_physics)
			std::cerr << "Failed to initilaize the PxPhysics object." << std::endl;

		physx::PxVec3 physxGravity(gravity.x, gravity.y, gravity.z);

		_sceneDesc = new physx::PxSceneDesc(_physics->getTolerancesScale());

		_sceneDesc->gravity = physxGravity;
		_scene = _physics->createScene(*_sceneDesc);

		return (_physics != NULL);
	}

	void PhysicsManager::stop()
	{
		if (_sceneDesc)
			delete _sceneDesc;

		if (_scene)
			_scene->release();
		if (_physics)
			_physics->release();
		if (_foundation)
			_foundation->release();
	}

	void PhysicsManager::simulate(float deltaTime)
	{
		_scene->simulate(deltaTime);
	}

	void PhysicsManager::fetchSimulationResults()
	{
		_scene->fetchResults(true);
	}

	void PhysicsManager::addActor(physx::PxActor* actor)
	{
		_scene->addActor(*actor);
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