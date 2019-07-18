#include "SimulationEventCallback.h"

SimulationEventCallback::SimulationEventCallback(physx::PxRigidActor* spaceshipActor) : physx::PxSimulationEventCallback(),
	_spaceshipActor(spaceshipActor)
{

}

SimulationEventCallback::~SimulationEventCallback()
{

}

void SimulationEventCallback::onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs,
										physx::PxU32 nbPairs)
{
	for (int i = 0; i < nbPairs; i++)
	{
		const physx::PxContactPair& cp = pairs[i];

		if (cp.events & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND)
		{
			if (pairHeader.actors[0] == _spaceshipActor || pairHeader.actors[1] == _spaceshipActor)
			{
				std::cout << "Collision detected!" << std::endl;
			}
		}
	}
}