#include <PxPhysicsAPI.h>
#include "Scene Graph/CapsuleCollider.h"

namespace gn
{
	CapsuleCollider::CapsuleCollider(GameObject* gameObject) : Collider(ComponentID::CapsuleCollider, gameObject)
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