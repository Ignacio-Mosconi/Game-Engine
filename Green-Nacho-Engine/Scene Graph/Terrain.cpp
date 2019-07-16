#include <PxPhysicsAPI.h>
#include "Scene Graph/Terrain.h"
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

		physx::PxReal heightScale = (physx::PxReal)scale.y / MAX_BYTE_VALUE;
		physx::PxReal rowScale = (physx::PxReal)scale.x;
		physx::PxReal columnScale = (physx::PxReal)scale.z;

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
}