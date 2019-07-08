#include "Scene Graph/NavigationController.h"
#include "Scene Graph/GameObject.h"
#include "Scene Graph/Transform.h"
#include "Core/InputManager.h"

namespace gn
{
	NavigationController::NavigationController(GameObject* gameObject) : Component(ComponentID::NAVIGATION_CONTROLLER, gameObject),
		_movementSpeed(10.0f), _rotationSpeed(90.0f), _horAngle(0.0f), _verAngle(0.0f)
	{

	}

	NavigationController::~NavigationController()
	{

	}

	void NavigationController::advance(float distance)
	{
		glm::vec3 newPos = _transform->getPosition() + _transform->getForward() * distance;		
		_transform->setPosition(newPos.x, newPos.y, newPos.z);
	}

	void NavigationController::strafe(float distance)
	{
		glm::vec3 newPos = _transform->getPosition() + _transform->getRight() * distance;
		_transform->setPosition(newPos.x, newPos.y, newPos.z);
	}

	void NavigationController::ascend(float distance)
	{
		glm::vec3 newPos = _transform->getPosition() + _transform->getUp() * distance;
		_transform->setPosition(newPos.x, newPos.y, newPos.z);
	}

	void NavigationController::move(MoveDir moveDir, float distance)
	{
		switch (moveDir)
		{
			case MoveDir::FORWARD:
				advance(distance);
				break;
			case MoveDir::BACKWARDS:
				advance(-distance);
				break;
			case MoveDir::LEFT:
				strafe(-distance);
				break;
			case MoveDir::RIGHT:
				strafe(distance);
				break;
			case MoveDir::UP:
				ascend(distance);
				break;
			case MoveDir::DOWN:
				ascend(-distance);
				break;
			default:
				break;
		}
	}

	void NavigationController::rotate(float horRotation, float verRotation)
	{
		_horAngle += horRotation;
		_verAngle += verRotation;

		_verAngle = glm::clamp(_verAngle, -VERTICAL_RANGE, VERTICAL_RANGE);

		_transform->setRotation(_verAngle, _horAngle, 0.0f);
		_transform->setUp(glm::vec3(0.0f, 1.0f, 0.0f));
	}

	void NavigationController::start()
	{
		_transform = _gameObject->getTransform();
		_transform->setRotation(0.0f, 180.0f, 0.0f);
		_horAngle = _transform->getRotation().y;
		_verAngle = _transform->getRotation().x;
		InputManager::getInstance()->hideCursor();
	}	
	
	void NavigationController::stop()
	{
		_transform = NULL;
		InputManager::getInstance()->showCursor();
	}

	void NavigationController::update(float deltaTime)
	{
		InputManager* inputManager = InputManager::getInstance();

		if (inputManager->getKey(Key::W))
			move(MoveDir::FORWARD, _movementSpeed * deltaTime);
		if (inputManager->getKey(Key::A))
			move(MoveDir::LEFT, _movementSpeed * deltaTime);
		if (inputManager->getKey(Key::S))
			move(MoveDir::BACKWARDS, _movementSpeed * deltaTime);
		if (inputManager->getKey(Key::D))
			move(MoveDir::RIGHT, _movementSpeed * deltaTime);
		if (inputManager->getKey(Key::Q))
			move(MoveDir::UP, _movementSpeed * deltaTime);
		if (inputManager->getKey(Key::E))
			move(MoveDir::DOWN, _movementSpeed * deltaTime);

		float horRotation = inputManager->getAxis(InputAxis::HORIZONTAL) * _rotationSpeed * deltaTime;
		float verRotation = inputManager->getAxis(InputAxis::VERTICAL) * _rotationSpeed * deltaTime;

		rotate(horRotation, verRotation);
	}

	void NavigationController::setSpeeds(float movementSpeed, float rotationSpeed)
	{
		_movementSpeed = movementSpeed;
		_rotationSpeed = rotationSpeed;
	}
}