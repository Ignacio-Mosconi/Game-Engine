#pragma once
#pragma warning(disable: 4251)

#include <iostream>
#include <glm/vec3.hpp>
#include "Exports.h"

namespace physx
{
	class PxFoundation;
	class PxPhysics;
	class PxScene;
	class PxActor;
}

namespace gn
{
	class ENGINE_API PhysicsManager
	{
	private:
		static PhysicsManager* _instance;
		
		physx::PxFoundation* _foundation;
		physx::PxPhysics* _physics;
		physx::PxScene* _scene;

		PhysicsManager();
		~PhysicsManager();

	public:
		static PhysicsManager* getInstance();
		static void deleteInstance();

		bool start(glm::vec3 gravity, unsigned int numThreads);
		void stop();

		void simulate(float deltaTime);
		void fetchSimulationResults();

		void addActor(physx::PxActor* actor);
	};
}