#pragma once
#pragma warning(disable: 4251)

#include <glm/glm.hpp>
#include <glm/geometric.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "Core/Exports.h"
#include "Scene Graph/Component.h"

namespace gn
{
	class BoundingBox;

	class ENGINE_DECL_SPEC BspPlane : public Component
	{
	private:
		glm::vec4 _plane;

	public:
		BspPlane(GameObject* gameObject);
		virtual ~BspPlane();

		void createPlane(glm::vec3 planeNormal, glm::vec3 pointInPlane);
		float getDistanceToPlane(glm::vec3 point) const;
		bool isBehindPlane(BoundingBox* boundingBox, glm::vec3 cameraPosition) const;
	};
}