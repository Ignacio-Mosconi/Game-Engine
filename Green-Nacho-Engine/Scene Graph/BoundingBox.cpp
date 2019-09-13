#include "Scene Graph/BoundingBox.h"
#include "Core/Renderer.h"
#include "Scene Graph/GameObject.h"
#include "Scene Graph/Transform.h"

namespace gn
{
	BoundingBox::BoundingBox(GameObject* gameObject) : Component(ComponentID::BOUNDING_BOX, gameObject),
		_transform(NULL), _maxs(std::numeric_limits<float>::min()), _mins(std::numeric_limits<float>::max())
	{

	}

	BoundingBox::~BoundingBox()
	{

	}

	void BoundingBox::start()
	{
		_transform = _gameObject->getTransform();
	}

	void BoundingBox::stop()
	{
		_transform = NULL;
	}

	void BoundingBox::update(float deltaTime)
	{
		updateVertices();
	}

	void BoundingBox::updateVertices()
	{
		std::vector<Component*> childrenBBs = _gameObject->getComponentsInChildren(ComponentID::BOUNDING_BOX);
		glm::vec3 globalPosition = getGameObject()->getTransform()->getGlobalPosition();
		glm::vec3 newMins = _mins;
		glm::vec3 newMaxs = _maxs;

		for (int i = 0; i < childrenBBs.size(); i++)
		{
			BoundingBox* childBB = (BoundingBox*)childrenBBs[i];
			glm::vec3 childGlobalPos = childBB->getGameObject()->getTransform()->getGlobalPosition();

			for (int j = 0; j < CUBE_VERTICES; j++)
			{
				glm::vec3 vertexGlobalPos = _vertices[j] + childGlobalPos;
				glm::vec3 vertexRelativePos = vertexGlobalPos - globalPosition;

				if (vertexRelativePos.x < _mins.x)
					newMins.x = vertexRelativePos.x;
				if (vertexRelativePos.y < _mins.y)
					newMins.y = vertexRelativePos.y;
				if (vertexRelativePos.z < _mins.z)
					newMins.z = vertexRelativePos.z;

				if (vertexRelativePos.x > _maxs.x)
					newMaxs.x = vertexRelativePos.x;
				if (vertexRelativePos.y > _maxs.y)
					newMaxs.y = vertexRelativePos.y;
				if (vertexRelativePos.z > _maxs.z)
					newMaxs.z = vertexRelativePos.z;
			}
		}

		setVertices(newMins, newMaxs);
	}
	
	void BoundingBox::setVertices(glm::vec3 mins, glm::vec3 maxs)
	{
		_mins = mins;
		_maxs = maxs;

		glm::vec3 vertices[CUBE_VERTICES] =
		{
			glm::vec3(mins.x, mins.y, mins.z),
			glm::vec3(mins.x, maxs.y, mins.z),
			glm::vec3(mins.x, mins.y, maxs.z),
			glm::vec3(mins.x, maxs.y, maxs.z),
			glm::vec3(maxs.x, mins.y, mins.z),
			glm::vec3(maxs.x, maxs.y, mins.z),
			glm::vec3(maxs.x, mins.y, maxs.z),
			glm::vec3(maxs.x, maxs.y, maxs.z)
		};

		for (int i = 0; i < CUBE_VERTICES; i++)
			_vertices[i] = vertices[i];
	}	

	glm::vec3 BoundingBox::getVertexGlobalPosition(unsigned int index) const
	{
		if (index > CUBE_VERTICES)
		{
			std::cerr << "WARNING: attempting to access an inexistent vertex." << std::endl;
			return glm::vec3(0.0f);
		}
	
		glm::vec4 globalPos(_vertices[index].x, _vertices[index].y, _vertices[index].z, 1.0f);

		globalPos = _gameObject->getRenderer()->getModelMatrix() * globalPos;

		return (glm::vec3)globalPos;
	}
}