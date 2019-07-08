#include "Scene Graph/BoundingBox.h"
#include "Scene Graph/GameObject.h"
#include "Scene Graph/Transform.h"

namespace gn
{
	BoundingBox::BoundingBox(GameObject* gameObject) : Component(ComponentID::BOUNDING_BOX, gameObject),
		_transform(NULL)
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

	void BoundingBox::setVertices(glm::vec3 vertices[CUBE_VERTICES])
	{
		for (int i = 0; i < CUBE_VERTICES; i++)
			_vertices[i] = vertices[i];
	}

	glm::vec3 BoundingBox::getVertexPosition(unsigned int index) const
	{
		if (index > CUBE_VERTICES)
		{
			std::cerr << "WARNING: attempting to access an inexistent vertex." << std::endl;
			return glm::vec3(0.0f);
		}

		return _vertices[index] + _transform->getPosition();
	}
}