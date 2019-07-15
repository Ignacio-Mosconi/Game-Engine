#include <PxPhysicsAPI.h>
#include "Scene Graph/BoxCollider.h"
#include "Scene Graph/BoundingBox.h"

namespace gn
{
	BoxCollider::BoxCollider(GameObject* gameObject) : Collider(ComponentID::BOX_COLLIDER, gameObject)
	{

	}

	BoxCollider::~BoxCollider()
	{

	}

	void BoxCollider::createGeometry(BoundingBox* boundingBox)
	{
		float halfWidth, halfHeight, halfDepth;

		glm::vec3 maxs = boundingBox->getMaxs();
		glm::vec3 mins = boundingBox->getMins();

		halfWidth = (maxs.x - mins.x) * 0.5f;
		halfHeight = (maxs.y - mins.y) * 0.5f;
		halfDepth = (maxs.z - mins.z) * 0.5f;

		_geometry = new physx::PxBoxGeometry(halfHeight, halfWidth, halfDepth);
	}

	void BoxCollider::createGeometry(float width, float height, float depth)
	{
		_geometry = new physx::PxBoxGeometry(height * 0.5f, width * 0.5f, depth * 0.5f);
	}	
}