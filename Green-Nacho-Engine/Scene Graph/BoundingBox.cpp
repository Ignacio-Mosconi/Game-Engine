#include "Scene Graph/BoundingBox.h"
#include "Core/Renderer.h"
#include "Core/Material.h"
#include "Scene Graph/GameObject.h"
#include "Scene Graph/Transform.h"

namespace gn
{
	BoundingBox::BoundingBox(GameObject* gameObject) : Component(ComponentID::BOUNDING_BOX, gameObject),
		_transform(NULL), _debugRenderMaterial(NULL), _maxs(-FLT_MAX), _mins(FLT_MAX)
	{

	}

	BoundingBox::~BoundingBox()
	{

	}

	void BoundingBox::start()
	{
		_transform = _gameObject->getTransform();
		_debugRenderMaterial = Material::generateMaterial(SIMPLE_VERTEX_SHADER_PATH, SIMPLE_PIXEL_SHADER_PATH);
	}

	void BoundingBox::stop()
	{
		_transform = NULL;
		Material::destroyMaterial(_debugRenderMaterial);
	}

	void BoundingBox::draw() const
	{
		Renderer* renderer = getGameObject()->getRenderer();

		_debugRenderMaterial->bind();
		_debugRenderMaterial->setMatrixProperty("MVP", renderer->getMVP());
		
		float* vertexBufferData = new float[VERTEX_COMPONENTS * LINE_VERTICES * 24]
		{
			_mins.x, _mins.y, _mins.z,
			_mins.x, _mins.y, _maxs.z,

			_mins.x, _mins.y, _mins.z,
			_mins.x, _maxs.y, _mins.z,
			
			_mins.x, _mins.y, _mins.z,
			_maxs.x, _mins.y, _mins.z,
			
			_maxs.x, _maxs.y, _mins.z,
			_mins.x, _maxs.y, _mins.z,
			
			_maxs.x, _maxs.y, _mins.z,
			_maxs.x, _mins.y, _mins.z,		
			
			_maxs.x, _maxs.y, _mins.z,
			_maxs.x, _maxs.y, _maxs.z,
			
			_mins.x, _maxs.y, _maxs.z,
			_maxs.x, _maxs.y, _maxs.z,			
			
			_mins.x, _maxs.y, _maxs.z,
			_mins.x, _mins.y, _maxs.z,			
			
			_mins.x, _maxs.y, _maxs.z,
			_mins.x, _maxs.y, _mins.z,			
			
			_maxs.x, _mins.y, _maxs.z,
			_mins.x, _mins.y, _maxs.z,			
			
			_maxs.x, _mins.y, _maxs.z,
			_maxs.x, _maxs.y, _maxs.z,			
			
			_maxs.x, _mins.y, _maxs.z,
			_maxs.x, _mins.y, _mins.z,
		};

		int vertexBufferSize = sizeof(float) * VERTEX_COMPONENTS * LINE_VERTICES * 12;
		unsigned int vertexBufferID = renderer->generateVertexBuffer(vertexBufferData, vertexBufferSize);

		renderer->enableAttribute(0);
		renderer->bindBuffer(0, VERTEX_COMPONENTS, vertexBufferID);
		renderer->drawBuffer(PrimitiveType::LINES, LINE_VERTICES * 12);
		renderer->disableAttribute(0);

		renderer->destroyBuffer(vertexBufferID);
		delete[] vertexBufferData;
	}

	void BoundingBox::updateVertices()
	{	
		glm::mat4 globalModelMatrix = _transform->getGlobalModelMatrix();
		glm::vec3 newMins(FLT_MAX);
		glm::vec3 newMaxs(-FLT_MAX);
		glm::vec3 newGlobalMins = (glm::vec3)(globalModelMatrix * glm::vec4(newMins.x, newMins.y, newMins.z, 1.0f));
		glm::vec3 newGlobalMaxs = (glm::vec3)(globalModelMatrix * glm::vec4(newMaxs.x, newMaxs.y, newMaxs.z, 1.0f));

		if (!_gameObject->getComponentInChildren(ComponentID::BOUNDING_BOX))
		{
			newMins = _mins;
			newMaxs = _maxs;
		}

		for (int i = 0; i < _gameObject->getChildCount(); i++)
		{
			BoundingBox* childBB = (BoundingBox*)_gameObject->getChild(i)->getComponent(ComponentID::BOUNDING_BOX);

			if (childBB)
			{
				childBB->updateVertices();

				for (int j = 0; j < CUBE_VERTICES; j++)
				{	
					glm::vec3 vertexGlobalPos = childBB->getVertexGlobalPosition(j);
					glm::vec3 vertexRelativePos = vertexGlobalPos - _transform->getGlobalPosition();
					glm::vec3 previousNewMins = newMins;
					glm::vec3 previousNewMaxs = newMaxs;

					if (vertexGlobalPos.x < newGlobalMins.x)
						newMins.x = vertexRelativePos.x;
					if (vertexGlobalPos.y < newGlobalMins.y)
						newMins.y = vertexRelativePos.y;
					if (vertexGlobalPos.z < newGlobalMins.z)
						newMins.z = vertexRelativePos.z;

					if (vertexGlobalPos.x > newGlobalMaxs.x)
						newMaxs.x = vertexRelativePos.x;
					if (vertexGlobalPos.y > newGlobalMaxs.y)
						newMaxs.y = vertexRelativePos.y;
					if (vertexGlobalPos.z > newGlobalMaxs.z)
						newMaxs.z = vertexRelativePos.z;

					if (newMins != previousNewMins)
						newGlobalMins = (glm::vec3)(globalModelMatrix * glm::vec4(newMins.x, newMins.y, newMins.z, 1.0f));
					if (newMaxs != previousNewMaxs)
						newGlobalMaxs= (glm::vec3)(globalModelMatrix * glm::vec4(newMaxs.x, newMaxs.y, newMaxs.z, 1.0f));
				}
			}
		}

		if (newMins != _mins || newMaxs != _maxs)
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
		glm::mat4 globalModelMatrix = _transform->getGlobalModelMatrix();

		globalPos = globalModelMatrix * globalPos;

		return (glm::vec3)globalPos;
	}	
	
	glm::vec3 BoundingBox::getMinsGlobalPosition() const
	{	
		glm::vec4 globalPos(_mins.x, _mins.y, _mins.z, 1.0f);
		glm::mat4 globalModelMatrix = _transform->getGlobalModelMatrix();

		globalPos = globalModelMatrix * globalPos;

		return (glm::vec3)globalPos;
	}	
	
	glm::vec3 BoundingBox::getMaxsGlobalPosition() const
	{	
		glm::vec4 globalPos(_maxs.x, _maxs.y, _maxs.z, 1.0f);
		glm::mat4 globalModelMatrix = _transform->getGlobalModelMatrix();
		
		globalPos = globalModelMatrix * globalPos;

		return (glm::vec3)globalPos;
	}
}