#include <PxPhysicsAPI.h>
#include "Scene Graph/CapsuleCollider.h"
#include "Scene Graph/BoundingBox.h"
#include "Scene Graph/GameObject.h"
#include "Scene Graph/Transform.h"

namespace gn
{
	CapsuleCollider::CapsuleCollider(GameObject* gameObject) : Collider(ComponentID::CAPSULE_COLLIDER, gameObject)
	{

	}
	
	CapsuleCollider::~CapsuleCollider()
	{

	}

	void CapsuleCollider::createGeometry(BoundingBox* boundingBox)
	{
		float radius, halfHeight;

		glm::vec3 maxs = boundingBox->getMaxs();
		glm::vec3 mins = boundingBox->getMins();

		radius = (maxs.x - mins.x) * 0.5f;
		halfHeight = (maxs.y - mins.y) * 0.5f;

		float scaleX = _gameObject->getTransform()->getScale().x;
		float scaleY = _gameObject->getTransform()->getScale().y;

		_geometry = new physx::PxCapsuleGeometry(radius * scaleX, halfHeight * scaleY);
	}
	
	void CapsuleCollider::createGeometry(float radius, float height)
	{
		_geometry = new physx::PxCapsuleGeometry(radius, height * 0.5f);
	}
}