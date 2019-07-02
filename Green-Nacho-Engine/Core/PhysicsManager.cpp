#include <PxPhysicsAPI.h>
#include "Core/PhysicsManager.h"
#include "Core/Renderer.h"

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

		_scene->setVisualizationParameter(physx::PxVisualizationParameter::eSCALE, 1.0f);
		_scene->setVisualizationParameter(physx::PxVisualizationParameter::eACTOR_AXES, 5.0f);
		_scene->setVisualizationParameter(physx::PxVisualizationParameter::eCOLLISION_SHAPES, 1.0f);

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

	void PhysicsManager::drawDebugVisualization(Renderer* renderer) const
	{
		const physx::PxRenderBuffer& rb = _scene->getRenderBuffer();
		
		for (unsigned int i = 0; i < rb.getNbLines(); i++)
		{
			const physx::PxDebugLine& line = rb.getLines()[i];
		
			float* vertexBufferData = new float[VERTEX_COMPONENTS * LINE_VERTICES]
			{
				line.pos0.x, line.pos0.y, line.pos0.z,
				line.pos1.x, line.pos1.y, line.pos1.z,
			};			
			int vertexBufferSize = sizeof(float) * VERTEX_COMPONENTS * LINE_VERTICES;
			unsigned int vertexBufferID = renderer->generateVertexBuffer(vertexBufferData, vertexBufferSize);

			renderer->loadIdentityMatrix();

			renderer->enableAttribute(0);
			renderer->bindBuffer(0, VERTEX_COMPONENTS, vertexBufferID);
			renderer->drawBuffer(PrimitiveType::LINES, LINE_VERTICES);
			renderer->disableAttribute(0);

			renderer->destroyBuffer(vertexBufferID);
			delete[] vertexBufferData;
		}
	}

	void PhysicsManager::addActor(physx::PxActor* actor)
	{
		_scene->addActor(*actor);
	}	
	
	void PhysicsManager::removeActor(physx::PxActor* actor)
	{
		_scene->removeActor(*actor);
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