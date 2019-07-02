#pragma once

#include <stack>
#include "Core/Exports.h"
#include "Scene Graph/Component.h"

namespace gn
{
	class Renderer;
	class GameObject;
	class Transform;

	class ENGINE_DECL_SPEC Camera : public Component
	{
	private:
		Renderer* _renderer;
		Transform* _transform;

	public:
		Camera(GameObject* gameObject);
		virtual ~Camera();

		void start() override;
		void stop() override;
		void update(float deltaTime) override;
	};
}
