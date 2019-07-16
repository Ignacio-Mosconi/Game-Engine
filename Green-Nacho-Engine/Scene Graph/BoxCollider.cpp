#include <PxPhysicsAPI.h>
#include "Scene Graph/BoxCollider.h"
#include "Scene Graph/BoundingBox.h"
#include "Scene Graph/GameObject.h"
#include "Scene Graph/Transform.h"

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

		float scaleX = _gameObject->getTransform()->getScale().x;
		float scaleY = _gameObject->getTransform()->getScale().y;
		float scaleZ = _gameObject->getTransform()->getScale().z;

		_geometry = new physx::PxBoxGeometry(halfHeight * scaleY, halfWidth * scaleX, halfDepth * scaleZ);
	}

	void BoxCollider::createGeometry(float width, float height, float depth)
	{
		_geometry = new physx::PxBoxGeometry(height * 0.5f, width * 0.5f, depth * 0.5f);
	}	
}