#pragma once
#pragma warning(disable: 4251)

#include <iostream>
#include <glm/vec3.hpp>
#include "Core/Exports.h"
#include "Core/EngineConstants.h"
#include "Core/Enums.h"

namespace physx
{
	class PxFoundation;
	class PxPhysics;
	class PxScene;
	class PxActor;
	class PxTransform;
	class PxRigidActor;
	class PxCapsuleGeometry;
	class PxMaterial;
}

namespace gn
{
	class Renderer;
	class Material;

	class ENGINE_DECL_SPEC PhysicsManager
	{
	private:
		static PhysicsManager* _instance;
		
		physx::PxFoundation* _foundation;
		physx::PxPhysics* _physics;
		physx::PxScene* _scene;

		Material* _debugRenderMaterial;

		PhysicsManager();
		~PhysicsManager();

	public:
		static PhysicsManager* getInstance();
		static void deleteInstance();

		bool start(glm::vec3 gravity, unsigned int numThreads);
		void stop();

		void simulate(float deltaTime);
		void fetchSimulationResults();
		
		void drawDebugVisualization(Renderer* renderer) const;

		void addActor(physx::PxActor* actor);
		void removeActor(physx::PxActor* actor);
		
		physx::PxMaterial* createPhysicsMaterial(float staticFriction, float dynamicFriction, float restitution);
		physx::PxRigidActor* createRigidActor(physx::PxTransform pxTransform, bool isStatic);
	};
}