#pragma once

#include <iostream>
#include <PxPhysicsAPI.h>


class SimulationEventCallback : public physx::PxSimulationEventCallback
{
private:
	physx::PxRigidActor* _spaceshipActor;

public:
	SimulationEventCallback(physx::PxRigidActor* spaceshipActor);
	~SimulationEventCallback();

	void onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, 
					physx::PxU32 nbPairs) override;
	void onConstraintBreak(physx::PxConstraintInfo *constraints, physx::PxU32 count) override {}
	void onWake(physx::PxActor** actors, physx::PxU32 count) override {}
	void onSleep(physx::PxActor** actors, physx::PxU32 count) override {}
	void onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count) override {}
	void onAdvance(const physx::PxRigidBody *const *bodyBuffer, const physx::PxTransform *poseBuffer, 
					const physx::PxU32 count) override {}
};