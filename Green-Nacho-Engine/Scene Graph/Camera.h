#pragma once
#pragma warning(disable: 4251)

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "Core/Exports.h"
#include "Scene Graph/Component.h"

namespace gn
{
	class Renderer;
	class GameObject;
	class Transform;
	class BoundingBox;

	enum class FrustumPlane
	{
		TOP, BOTTOM, LEFT, RIGHT, NEAR, FAR, COUNT
	};

	class ENGINE_DECL_SPEC Camera : public Component
	{
	private:
		Renderer* _renderer;
		Transform* _transform;

		glm::vec4 _frustumPlanes[(int)FrustumPlane::COUNT];
		glm::vec3 _globalPosition;
		glm::vec3 _viewDirection;

		float _nearDistance;
		float _farDistance;
		float _fovTangent;
		float _halfNearHeight;
		float _halfNearWidth;
		float _halfFarHeight;
		float _halfFarWidth;

		glm::vec4 generatePlane(glm::vec3 normal, glm::vec3 point);

	public:
		Camera(GameObject* gameObject);
		virtual ~Camera();

		void start() override;
		void stop() override;
		void update(float deltaTime) override;

		void updateView();
		void updateFrustum();
		void updateFrustumProperties(float fieldOfView, float aspectRatio, float nearDistance, float farDistance);

		void setViewDirection(glm::vec3 viewDirection);

		bool isInsideFrustum(BoundingBox* boundingBox);
	};
}
