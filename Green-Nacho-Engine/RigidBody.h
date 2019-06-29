#pragma once

#include "Exports.h"
#include "Component.h"

namespace physx
{
	class PxRigidActor;
	class PxShape;
	class PxGeometry;
}

namespace gn
{
	class Transform;

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

		void createRigidBody(Transform* transform, physx::PxGeometry geometry, bool isStatic);
	};
}
