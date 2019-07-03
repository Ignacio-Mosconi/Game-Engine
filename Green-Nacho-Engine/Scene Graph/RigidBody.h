#pragma once
#pragma warning(disable: 4251)

#include "Core/Exports.h"
#include "Scene Graph/Component.h"
#include "Core/Enums.h"

namespace physx
{
	struct PxForceMode;
	class PxRigidActor;
	class PxShape;
	class PxMaterial; 
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
		physx::PxMaterial* _material;

		bool _isStatic;

	public:
		RigidBody(GameObject* gameObject);
		virtual ~RigidBody();

		void start() override;
		void stop() override;
		void update(float deltaTime) override;

		void createRigidBody(Collider* collider, bool isStatic = false, float mass = 1.0f, 
							glm::vec3 colliderOffset = glm::vec3(0.0f, 0.0f, 0.0f));
		void disposeRigidBody();

		void addForce(glm::vec3 force, ForceMode forceMode);
	};
}
