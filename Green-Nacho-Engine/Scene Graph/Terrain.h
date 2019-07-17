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
	class PxHeightFieldGeometry;
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
		physx::PxHeightFieldGeometry* _geometry;
		physx::PxMaterial* _material;
		physx::PxShape* _shape;

		int _heightmapRows;
		int _heightmapColumns;
		std::vector<std::vector<int>> _heights;
		glm::vec3 _scale;

	public:
		Terrain(GameObject* gameObject);
		virtual ~Terrain();

		void stop() override;

		void createHeightField(std::vector<std::vector<int>> heights, int rows, int columns, glm::vec3 scale);
		void disposeHeightField();

		void flattenArea(int startRow, int endRow, int startColumn, int endColumn, int height);

		inline int getHeightmapRows() const { return _heightmapRows; }
		inline int getHeightmapColumns() const { return _heightmapColumns; }
		inline glm::vec3 getScale() const { return _scale; }
	};
}
