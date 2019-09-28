#include "Scene Graph/BspPlane.h"
#include "Scene Graph/BoundingBox.h"

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

	bool BspPlane::isBehindPlane(BoundingBox* boundingBox, glm::vec3 cameraPosition) const
	{
		bool isBehindPlane = false;
		float cameraDistanceToPlane = getDistanceToPlane(cameraPosition);
		float cameraDistanceSign = glm::sign(cameraDistanceToPlane);

		for (int j = 0; j < CUBE_VERTICES; j++)
		{
			glm::vec3 vertexPosition = boundingBox->getVertexGlobalPosition(j);
			float vertexDistanceToPlane = getDistanceToPlane(vertexPosition);
			float vertexDistanceSign = glm::sign(vertexDistanceToPlane);

			if (vertexDistanceSign == cameraDistanceSign)
				break;
			if (j == CUBE_VERTICES - 1)
				isBehindPlane = true;
		}

		return isBehindPlane;
	}

	float BspPlane::getDistanceToPlane(glm::vec3 point) const
	{
		float distance = 0.0f;
		glm::vec3 planeNormal = glm::vec3(_plane);

		distance = glm::dot(planeNormal, point) + _plane.w;

		return distance;
	}
}