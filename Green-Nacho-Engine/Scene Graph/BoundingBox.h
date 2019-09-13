#pragma once
#pragma warning(disable: 4251)

#include <limits>
#include <glm/vec3.hpp>
#include "Core/Exports.h"
#include "Core/EngineConstants.h"
#include "Scene Graph/Component.h"

namespace gn
{
	class GameObject;
	class Transform;

	class ENGINE_DECL_SPEC BoundingBox : public Component
	{
	private:
		Transform* _transform;
		glm::vec3 _vertices[CUBE_VERTICES];
		
		glm::vec3 _maxs;
		glm::vec3 _mins;

	public:
		BoundingBox(GameObject* gameObject);
		virtual ~BoundingBox();

		void start() override;
		void stop() override;
		void update(float deltaTime) override;

		void updateVertices();
		void setVertices(glm::vec3 mins, glm::vec3 maxs);

		glm::vec3 getVertexGlobalPosition(unsigned int index) const;

		inline glm::vec3 getMaxs() const { return _maxs; }
		inline glm::vec3 getMins() const { return _mins; }
	};
}