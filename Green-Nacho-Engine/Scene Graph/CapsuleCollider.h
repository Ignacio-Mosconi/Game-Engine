#pragma once

#include "Core/Exports.h"
#include "Scene Graph/Collider.h"

namespace gn
{
	class BoundingBox;

	class ENGINE_DECL_SPEC CapsuleCollider : public Collider
	{
	public:
		CapsuleCollider(GameObject* gameObject);
		~CapsuleCollider();
		
		void createGeometry(BoundingBox* boundingBox) override;
		void createGeometry(float radius, float height);
	};
}
