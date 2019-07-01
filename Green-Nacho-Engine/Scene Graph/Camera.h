#pragma once

#include "Core/Exports.h"
#include "Scene Graph/Component.h"

namespace gn
{
	class Renderer;
	class Transform;

	class ENGINE_DECL_SPEC Camera : public Component
	{
	private:
		Renderer* _renderer;
		Transform* _transform;

	public:
		Camera();
		virtual ~Camera();

		void update() override;
		void stop() override;

		void activate(Renderer* renderer, Transform* transform);
		void deactivate();
	};
}
