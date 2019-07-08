#pragma once

#include "Exports.h"
#include "Component.h"

namespace physx
{
	class PxRigidActor;
	class PxShape;
}

namespace gn
{
	class Transform;
	class Collider;

	class ENGINE_DECL_SPEC RigidBody : public Component
	{
	private:
		Transform* _transform;

		physx::PxRigidActor* _rigidActor;
		physx::PxShape* _shape;

	public:
		RigidBody();
		virtual ~RigidBody();

		void start() override;
		void stop() override;
		void update() override;

		void createRigidBody(Transform* transform, Collider* collider, bool isStatic);
	};
}
