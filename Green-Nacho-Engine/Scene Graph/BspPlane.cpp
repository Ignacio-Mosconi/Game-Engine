#include "Scene Graph/BspPlane.h"

namespace gn
{
	BspPlane::BspPlane(GameObject* gameObject) : Component(ComponentID::BSP_PLANE, gameObject)
	{

	}

	BspPlane::~BspPlane()
	{

	}

	void BspPlane::createPlane(glm::vec3 planeNormal, glm::vec3 pointInPlane)
	{
		_plane.x = planeNormal.x;
		_plane.y = planeNormal.y;
		_plane.z = planeNormal.z;
		_plane.w = -glm::dot(planeNormal, pointInPlane);
	}

	float BspPlane::getDistanceToPlane(glm::vec3 point) const
	{
		float distance = 0.0f;
		glm::vec3 planeNormal = glm::vec3(_plane);

		distance = glm::dot(planeNormal, point) + _plane.w;

		return distance;
	}
}