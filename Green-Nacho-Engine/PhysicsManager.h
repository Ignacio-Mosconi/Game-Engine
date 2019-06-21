#pragma once
#pragma warning(disable: 4251)

#include <iostream>
#include "Exports.h"

namespace physx
{
	class PxFoundation;
	class PxPhysics;
}

namespace gn
{
	class ENGINE_API PhysicsManager
	{
	private:
		static PhysicsManager* _instance;
		
		physx::PxFoundation* _foundation;
		physx::PxPhysics* _physics;

		PhysicsManager();
		~PhysicsManager();

	public:
		static PhysicsManager* getInstance();
		static void deleteInstance();

		bool start();
		void stop();
	};
}