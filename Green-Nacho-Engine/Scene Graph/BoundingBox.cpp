#include "Scene Graph/BoundingBox.h"
#include "Core/Renderer.h"
#include "Scene Graph/GameObject.h"
#include "Scene Graph/Transform.h"

namespace gn
{
	BoundingBox::BoundingBox(GameObject* gameObject) : Component(ComponentID::BOUNDING_BOX, gameObject),
		_transform(NULL), _maxs(0.0f), _mins(0.0f)
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
		{	
			_vertices[i] = vertices[i];

			if (_vertices[i].x > _maxs.x)
				_maxs.x = _vertices[i].x;
			if (_vertices[i].y > _maxs.y)
				_maxs.y = _vertices[i].y;
			if (_vertices[i].z > _maxs.z)
				_maxs.z = _vertices[i].z;

			if (_vertices[i].x < _mins.x)
				_mins.x = _vertices[i].x;
			if (_vertices[i].y < _mins.y)
				_mins.y = _vertices[i].y;
			if (_vertices[i].z < _mins.z)
				_mins.z = _vertices[i].z;
		}
	}

	glm::vec3 BoundingBox::getVertexGlobalPosition(unsigned int index) const
	{
		if (index > CUBE_VERTICES)
		{
			std::cerr << "WARNING: attempting to access an inexistent vertex." << std::endl;
			return glm::vec3(0.0f);
		}
	
		glm::vec4 globalRotatedPos(_vertices[index].x, _vertices[index].y, _vertices[index].z, 1.0f);

		globalRotatedPos = _gameObject->getRenderer()->getModelMatrix() * globalRotatedPos;

		return (glm::vec3)globalRotatedPos;
	}
}