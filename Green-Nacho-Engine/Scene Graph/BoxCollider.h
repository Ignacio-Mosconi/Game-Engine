#pragma once

#include <glm/vec3.hpp>
#include "Core/Exports.h"
#include "Scene Graph/Collider.h"

namespace gn
{
	class BoundingBox;

	class ENGINE_DECL_SPEC BoxCollider : public Collider
	{
	public:
		BoxCollider(GameObject* gameObject);
		~BoxCollider();

		void createGeometry(BoundingBox* boundingBox) override;
		void createGeometry(float width, float height, float depth);
	};
}
