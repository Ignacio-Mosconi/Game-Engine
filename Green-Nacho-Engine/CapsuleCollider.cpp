#include <PxPhysicsAPI.h>
#include "CapsuleCollider.h"

namespace gn
{
	CapsuleCollider::CapsuleCollider() : Collider(ComponentID::CapsuleCollider)
	{

	}
	
	CapsuleCollider::~CapsuleCollider()
	{

	}	
	
	void CapsuleCollider::createCapsule(float radius, float halfHeight)
	{
		_geometry = new physx::PxCapsuleGeometry(radius, halfHeight);
	}
}