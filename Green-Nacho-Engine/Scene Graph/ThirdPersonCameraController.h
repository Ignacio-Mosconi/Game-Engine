#pragma once

#include <glm/glm.hpp>
#include "Core/Exports.h"
#include "Scene Graph/Component.h"

namespace gn
{
	class GameObject;
	class Transform;

	class ENGINE_DECL_SPEC ThirdPersonCameraController : public Component
	{
	private:
		Transform* _cameraTransform;
		Transform* _followTargetTransform;
		
		glm::vec3 _initialPivotForward;
		glm::vec3 _initialPivotUp;
		glm::vec3 _initialPivotRight;

		float _rotationSpeed;
		float _horAngle;
		float _verAngle;
		float _radius;
		
		const float VERTICAL_RANGE = 70.0f;

		void rotate(float horRotation, float verRotation);

	public:
		ThirdPersonCameraController(GameObject* gameObject);
		virtual ~ThirdPersonCameraController();

		void start() override;
		void stop() override;
		void update(float deltaTime) override;

		void setTransforms(Transform* cameraTransform, Transform* followTargetTransform);
		
		void setRotationSpeed(float rotationSpeed) { _rotationSpeed = rotationSpeed; }
		void setRadius(float radius) { _radius = radius; }
	};
}
