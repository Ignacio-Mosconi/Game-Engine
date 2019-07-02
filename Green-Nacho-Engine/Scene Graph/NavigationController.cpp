#include "Scene Graph/NavigationController.h"
#include "Scene Graph/GameObject.h"
#include "Scene Graph/Transform.h"
#include "Core/InputManager.h"

namespace gn
{
	NavigationController::NavigationController(GameObject* gameObject) : Component(ComponentID::NavigationController, gameObject)
	{
		InputManager::getInstance()->hideCursor();
	}

	NavigationController::~NavigationController()
	{

	}

	void NavigationController::advance(float distance)
	{
		glm::vec3 newPos = _transform->getPosition() - _transform->getForward() * distance;		
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

	void NavigationController::start()
	{
		_transform = _gameObject->getTransform();
	}	
	
	void NavigationController::stop()
	{
		_transform = NULL;
	}

	void NavigationController::update(float deltaTime)
	{
		InputManager* inputManager = InputManager::getInstance();

		if (inputManager->getKey(Key::W_KEY))
			move(MoveDir::FORWARD, _movementSpeed * deltaTime);
		if (inputManager->getKey(Key::A_KEY))
			move(MoveDir::LEFT, _movementSpeed * deltaTime);
		if (inputManager->getKey(Key::S_KEY))
			move(MoveDir::BACKWARDS, _movementSpeed * deltaTime);
		if (inputManager->getKey(Key::D_KEY))
			move(MoveDir::RIGHT, _movementSpeed * deltaTime);
		if (inputManager->getKey(Key::Q_KEY))
			move(MoveDir::UP, _movementSpeed * deltaTime);
		if (inputManager->getKey(Key::E_KEY))
			move(MoveDir::DOWN, _movementSpeed * deltaTime);

		float horRotation = inputManager->getAxis(InputAxis::HORIZONTAL) * _rotationSpeed * deltaTime;
		float verRotation = inputManager->getAxis(InputAxis::VERTICAL) * _rotationSpeed * deltaTime;

		_transform->rotate(verRotation, horRotation, 0.0f);

		float pitch = _transform->getRotation().x;
		glm::vec3 newUp = (pitch <= 90.0f || pitch > 180.0f) ? glm::vec3(0.0f, 1.0f, 0.0f) : glm::vec3(0.0f, -1.0f, 0.0f);
		_transform->setUp(newUp);
	}

	void NavigationController::setSpeeds(float movementSpeed, float rotationSpeed)
	{
		_movementSpeed = movementSpeed;
		_rotationSpeed = rotationSpeed;
	}
}