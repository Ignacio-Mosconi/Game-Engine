#pragma once
#pragma warning(disable: 4251)

#include <vector>
#include <glm/vec3.hpp>
#include "Core/Exports.h"
#include "Scene Graph/Component.h"

namespace physx
{
	class PxHeightField;
	class PxRigidActor;
	class PxMaterial;
	class PxShape;
}

namespace gn
{
	class ENGINE_DECL_SPEC Terrain : public Component
	{
	private:
		physx::PxHeightField* _heightField;
		physx::PxRigidActor* _rigidActor;
		physx::PxMaterial* _material;
		physx::PxShape* _shape;

		int _heightmapRows;
		int _heightmapColumns;
		std::vector<std::vector<float>> _heights;

	public:
		Terrain(GameObject* gameObject);
		virtual ~Terrain();

		void stop() override;

		void createHeightField(std::vector<std::vector<float>> heights, int rows, int columns, glm::vec3 scale);
		void disposeHeightField();
	};
}
