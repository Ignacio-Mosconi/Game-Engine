#pragma once

#include "Core/Exports.h"
#include "Core/Enums.h"
#include "Scene Graph/Component.h"

namespace gn
{
	class Transform;

	class ENGINE_DECL_SPEC NavigationController : public Component
	{
	private:
		Transform* _transform;

		float _movementSpeed;
		float _rotationSpeed;

		void advance(float distance);
		void strafe(float distance);
		void ascend(float distance);
		
		void move(MoveDir moveDir, float distance);

	public:
		NavigationController();
		virtual ~NavigationController();

		void update(float deltaTime) override;

		void activate(Transform* transform, float movementSpeed = 10.0f, float rotationSpeed = 10.0f);
		void deactivate();
	};
}