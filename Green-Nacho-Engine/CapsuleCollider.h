#pragma once

#include "Exports.h"
#include "Collider.h"

namespace gn
{
	class ENGINE_DECL_SPEC CapsuleCollider : public Collider
	{
	public:
		CapsuleCollider();
		~CapsuleCollider();
		
		void createCapsule(float radius, float halfHeight);
	};
}
