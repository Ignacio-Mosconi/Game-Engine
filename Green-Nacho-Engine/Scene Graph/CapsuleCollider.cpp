#include <PxPhysicsAPI.h>
#include "Scene Graph/CapsuleCollider.h"

namespace gn
{
	CapsuleCollider::CapsuleCollider(GameObject* gameObject) : Collider(ComponentID::CAPSULE_COLLIDER, gameObject)
	{

	}
	
	CapsuleCollider::~CapsuleCollider()
	{

	}	
	
	void CapsuleCollider::createCapsule(float radius, float height)
	{
		_geometry = new physx::PxCapsuleGeometry(radius, height * 0.5f);
	}
}