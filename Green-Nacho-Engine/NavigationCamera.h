#pragma once

#include "Camera.h"
#include "InputManager.h"
#include "Exports.h"

namespace gn
{
	namespace legacy
	{
		class ENGINE_DECL_SPEC NavigationCamera : public Camera
		{
			float _movementSpeed;
			float _rotationSpeed;

			void move(MoveDir moveDir, float distance);

		public:
			NavigationCamera(Renderer* renderer, float movementSpeed = 5.0f, float rotationSpeed = 270.0f);
			NavigationCamera(Renderer* renderer, float posX, float posY, float posZ,
				float movementSpeed = 5.0f, float rotationSpeed = 100.0f);
			~NavigationCamera();

			void update(float deltaTime);
		};
	}
}