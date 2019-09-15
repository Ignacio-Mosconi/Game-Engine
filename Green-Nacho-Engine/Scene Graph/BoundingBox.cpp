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
		glm::vec3 newMins = _mins;
		glm::vec3 newMaxs = _maxs;
		glm::vec3 globalMins = getMinsGlobalPosition();
		glm::vec3 globalMaxs = getMaxsGlobalPosition();

		for (int i = 0; i < _gameObject->getChildCount(); i++)
		{
			BoundingBox* childBB = (BoundingBox*)_gameObject->getChild(i)->getComponent(ComponentID::BOUNDING_BOX);

			if (childBB)
			{
				childBB->updateVertices();

				for (int j = 0; j < CUBE_VERTICES; j++)
				{	
					glm::vec3 vertexGlobalPos = childBB->getVertexGlobalPosition(j);
					glm::vec3 vertexLocalPos = childBB->getVertex(j);

					if (vertexGlobalPos.x < globalMins.x)
						newMins.x = vertexLocalPos.x;
					if (vertexGlobalPos.y < globalMins.y)
						newMins.y = vertexLocalPos.y;
					if (vertexGlobalPos.z < globalMins.z)
						newMins.z = vertexLocalPos.z;

					if (vertexGlobalPos.x > globalMaxs.x)
						newMaxs.x = vertexLocalPos.x;
					if (vertexGlobalPos.y > globalMaxs.y)
						newMaxs.y = vertexLocalPos.y;
					if (vertexGlobalPos.z > globalMaxs.z)
						newMaxs.z = vertexLocalPos.z;
				}
			}
		}

		//if (newMins != _mins || newMaxs != _maxs)
			//setVertices(newMins, newMaxs);
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

		globalPos = _gameObject->getRenderer()->getModelMatrix() * globalPos;

		return (glm::vec3)globalPos;
	}	
	
	glm::vec3 BoundingBox::getMaxsGlobalPosition() const
	{	
		glm::vec4 globalPos(_maxs.x, _maxs.y, _maxs.z, 1.0f);

		globalPos = _gameObject->getRenderer()->getModelMatrix() * globalPos;

		return (glm::vec3)globalPos;
	}
}