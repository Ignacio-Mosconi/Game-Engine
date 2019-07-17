#include "Scene Graph/ThirdPersonCameraController.h"
#include "Core/InputManager.h"
#include "Scene Graph/GameObject.h"
#include "Scene Graph/Transform.h"

namespace gn
{
	ThirdPersonCameraController::ThirdPersonCameraController(GameObject* gameObject) : 
		Component(ComponentID::THIRD_PERSON_CAMERA_CONTROLLER, gameObject),
		_cameraTransform(NULL), _followTargetTransform(NULL),
		_rotationSpeed(90.0f), _horAngle(-90.0f), _verAngle(0.0f), _radius(200.0f)
	{

	}

	ThirdPersonCameraController::~ThirdPersonCameraController()
	{

	}

	void ThirdPersonCameraController::rotate(float horRotation, float verRotation)
	{
		glm::vec3 newCameraPosition = _cameraTransform->getPosition();

		_horAngle += horRotation;
		_verAngle += verRotation;

		_verAngle = glm::clamp(_verAngle, -VERTICAL_RANGE, VERTICAL_RANGE);

		newCameraPosition.x = _initialPivotRight.x * glm::cos(glm::radians(_horAngle)) * _radius;
		newCameraPosition.y = _initialPivotUp.y * glm::sin(glm::radians(_verAngle)) * _radius;
		newCameraPosition.z = _initialPivotForward.z * glm::sin(glm::radians(_horAngle)) * _radius;

		glm::vec3 diff = _followTargetTransform->getGlobalPosition() - _cameraTransform->getGlobalPosition();

		_cameraTransform->setPosition(newCameraPosition.x, newCameraPosition.y, newCameraPosition.z);
		_cameraTransform->forceLocalForward(diff);
	}

	void ThirdPersonCameraController::start()
	{
		InputManager::getInstance()->hideCursor();
	}

	void ThirdPersonCameraController::stop()
	{
		InputManager::getInstance()->showCursor();
	}

	void ThirdPersonCameraController::update(float deltaTime)
	{
		InputManager* inputManager = InputManager::getInstance();

		float horRotation = inputManager->getAxis(InputAxis::HORIZONTAL) * _rotationSpeed * deltaTime;
		float verRotation = inputManager->getAxis(InputAxis::VERTICAL) * _rotationSpeed * deltaTime;

		rotate(horRotation, verRotation);
	}

	void ThirdPersonCameraController::setTransforms(Transform* cameraTransform, Transform* followTargetTransform)
	{
		_cameraTransform = cameraTransform;
		_followTargetTransform = followTargetTransform;

		_initialPivotForward = _followTargetTransform->getForward();
		_initialPivotUp = _followTargetTransform->getUp();
		_initialPivotRight = _followTargetTransform->getRight();
	}
}