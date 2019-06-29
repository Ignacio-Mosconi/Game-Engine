#include <PxPhysicsAPI.h>
#include "PhysicsManager.h"

namespace gn
{
	PhysicsManager* PhysicsManager::_instance = NULL;

	PhysicsManager::PhysicsManager() : _foundation(NULL), _physics(NULL), _scene(NULL)
	{

	}

	PhysicsManager::~PhysicsManager()
	{

	}

	bool PhysicsManager::start(glm::vec3 gravity, unsigned int numThreads)
	{
		static physx::PxDefaultAllocator defaultAllocator;
		static physx::PxDefaultErrorCallback defaultErrorCallback;

		_foundation = PxCreateFoundation(PX_PHYSICS_VERSION, defaultAllocator, defaultErrorCallback);
		if (!_foundation)
		{
			std::cerr << "Failed to initilaize the PxFoundation object." << std::endl;
			return false;
		}

		_physics = PxCreatePhysics(PX_PHYSICS_VERSION, *_foundation, physx::PxTolerancesScale());
		if (!_physics)
		{
			std::cerr << "Failed to initilaize the PxPhysics object." << std::endl;
			return false;
		}
		
		physx::PxSceneDesc sceneDesc(_physics->getTolerancesScale());
		
		physx::PxVec3 physxGravity(gravity.x, gravity.y, gravity.z);
		sceneDesc.gravity = physxGravity;
		
		if (!sceneDesc.cpuDispatcher)
		{
			physx::PxDefaultCpuDispatcher* cpuDispatcher = physx::PxDefaultCpuDispatcherCreate(numThreads);
			sceneDesc.cpuDispatcher = cpuDispatcher;
		}

		if (!sceneDesc.filterShader)
			sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
		
		if (!sceneDesc.isValid())
		{
			std::cerr << "The Scene descriptor is not valid" << std::endl;
			return false;
		}

		_scene = _physics->createScene(sceneDesc);
		if (!_scene)
		{
			std::cerr << "Failed to create the PxScene object" << std::endl;
			return false;
		}

		return true;
	}

	void PhysicsManager::stop()
	{
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
	
	void PhysicsManager::removeActor(physx::PxActor* actor)
	{
		_scene->removeActor(*actor);
	}

	physx::PxCapsuleGeometry PhysicsManager::createCapsuleGeometry(float radius, float halfHeight)
	{
		return physx::PxCapsuleGeometry(radius, halfHeight);
	}

	physx::PxMaterial* PhysicsManager::createPhysicsMaterial(float staticFriction, float dynamicFriction, float restitution)
	{
		return _physics->createMaterial(staticFriction, dynamicFriction, restitution);
	}
	
	physx::PxRigidActor* PhysicsManager::createRigidActor(physx::PxTransform pxTransform, bool isStatic)
	{
		physx::PxRigidActor* rigidActor = NULL;

		rigidActor = (isStatic) ? (physx::PxRigidActor*)_physics->createRigidStatic(pxTransform) : 
									(physx::PxRigidActor*)_physics->createRigidDynamic(pxTransform);

		return rigidActor;
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