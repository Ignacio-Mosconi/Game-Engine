#pragma once

#include "Core/Exports.h"
#include "Scene Graph/Collider.h"

namespace gn
{
	class ENGINE_DECL_SPEC CapsuleCollider : public Collider
	{
	public:
		CapsuleCollider(GameObject* gameObject);
		~CapsuleCollider();
		
		void createCapsule(float radius, float halfHeight);
	};
}
