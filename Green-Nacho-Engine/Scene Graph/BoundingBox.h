#pragma once

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

	public:
		BoundingBox(GameObject* gameObject);
		virtual ~BoundingBox();

		void start() override;
		void stop() override;

		void setVertices(glm::vec3 vertices[CUBE_VERTICES]);

		glm::vec3 getVertexPosition(unsigned int index) const;
	};
}