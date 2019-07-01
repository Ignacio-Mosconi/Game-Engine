#include <PxPhysicsAPI.h>
#include "Scene Graph/CapsuleCollider.h"

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