#include <PxPhysicsAPI.h>
#include "Scene Graph/Terrain.h"
#include "Scene Graph/GameObject.h"
#include "Scene Graph/MeshRenderer.h"
#include "Core/PhysicsManager.h"

namespace gn
{
	Terrain::Terrain(GameObject* gameObject) : Component(ComponentID::TERRAIN, gameObject)
	{

	}

	Terrain::~Terrain()
	{

	}	
	
	void Terrain::stop()
	{
		disposeHeightField();
	}

	void Terrain::createHeightField(std::vector<std::vector<int>> heights, int rows, int columns, glm::vec3 scale)
	{
		_heights = heights;
		_heightmapRows = rows;
		_heightmapColumns = columns;
		_scale = scale;

		physx::PxHeightFieldSample* samplesData = new physx::PxHeightFieldSample[sizeof(physx::PxHeightFieldSample) * rows * columns];
		physx::PxHeightFieldDesc hfDesc;
		
		hfDesc.nbRows = (physx::PxU32)_heightmapRows;
		hfDesc.nbColumns = (physx::PxU32)_heightmapColumns;
		hfDesc.samples.data = samplesData;
		hfDesc.samples.stride = sizeof(physx::PxHeightFieldSample);

		physx::PxHeightFieldSample* currentSample = samplesData;

		for (int row = 0; row < _heightmapRows; row++)
		{
			for (int col = 0; col < _heightmapColumns; col++)
			{
				currentSample->height = (physx::PxI16)_heights[col][row];
				currentSample->materialIndex0 = 0;
				currentSample->materialIndex1 = 0;
				currentSample->clearTessFlag();
				currentSample++;
			}
		}

		PhysicsManager* physicsManager = PhysicsManager::getInstance();

		physx::PxReal heightScale = (physx::PxReal)_scale.y / MAX_BYTE_VALUE;
		physx::PxReal rowScale = (physx::PxReal)_scale.x;
		physx::PxReal columnScale = (physx::PxReal)_scale.z;

		physx::PxTransform relativePose(physx::PxIdentity);
		
		_heightField = physicsManager->createHeighField(hfDesc);
		_geometry = new physx::PxHeightFieldGeometry(_heightField, physx::PxMeshGeometryFlags(), heightScale, rowScale, columnScale);
		_rigidActor = physicsManager->createRigidActor(relativePose, true);
		_material = physicsManager->createPhysicsMaterial(0.1f, 0.1f, 0.1f);
		_shape = physx::PxRigidActorExt::createExclusiveShape(*_rigidActor, *_geometry, *_material);

		physicsManager->addActor(_rigidActor);
	}

	void Terrain::disposeHeightField()
	{
		if (_heightField)
			_heightField->release();
		if (_geometry)
			delete _geometry;
		if (_rigidActor)
		{
			if (_material)
				_material->release();
			if (_shape)
				_rigidActor->detachShape(*_shape);
			PhysicsManager::getInstance()->removeActor(_rigidActor);
			_rigidActor->release();
		}
	}

	void Terrain::flattenArea(int startRow, int endRow, int startColumn, int endColumn, int flattenHeight)
	{
		std::vector<MeshVertex> vertices;

		flattenHeight = glm::clamp(flattenHeight, 0, (int)MAX_BYTE_VALUE);

		for (int row = 0; row < _heightmapRows; row++)
		{
			for (int col = 0; col < _heightmapColumns; col++)
			{
				MeshVertex vertex;

				float posX = col * _scale.x;
				float posZ = row * _scale.z;
				
				float posY = 0.0f;
				
				if (row >= startRow && row <= endRow && col >= startColumn && col <= endColumn)
				{
					posY = flattenHeight / MAX_BYTE_VALUE * _scale.y;
					_heights[row][col] = flattenHeight;
				}
				else
					posY = (float)_heights[row][col] / MAX_BYTE_VALUE * _scale.y;

				float u = (float)col / (float)_heightmapColumns;
				float v = 1.0f - (float)row / (float)_heightmapRows;

				vertex.position = glm::vec3(posX, posY, posZ);
				vertex.normal = glm::vec3(0.0f);
				vertex.uvCoord = glm::vec2(u, v);

				vertices.push_back(vertex);
			}
		}

		createHeightField(_heights, _heightmapRows, _heightmapColumns, _scale);

		MeshRenderer* meshRenderer = (MeshRenderer*)_gameObject->getComponent(ComponentID::MESH_RENDERER);
		meshRenderer->createMesh(vertices, meshRenderer->getIndexBufferData(), meshRenderer->getDiffuseTextures());
	}
}