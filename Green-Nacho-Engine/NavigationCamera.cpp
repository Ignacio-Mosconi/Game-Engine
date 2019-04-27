#include "NavigationCamera.h"

namespace gn
{
	NavigationCamera::NavigationCamera(gn::Renderer* renderer, float movementSpeed, float rotationSpeed) :
	Camera(renderer, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
	_movementSpeed(movementSpeed), _rotationSpeed(rotationSpeed)
	{
		InputManager::getInstance()->hideCursor();
	}

	NavigationCamera::NavigationCamera(gn::Renderer* renderer, float posX, float posY, float posZ,
	float movementSpeed, float rotationSpeed) : 
	Camera(renderer, glm::vec3(posX, posY, posZ), glm::vec3(0.0f, 0.0f, 0.0f)),
	_movementSpeed(movementSpeed), _rotationSpeed(rotationSpeed)
	{
		InputManager::getInstance()->hideCursor();
	}

	NavigationCamera::~NavigationCamera()
	{

	}

	void NavigationCamera::move(MoveDir moveDir, float distance)
	{
		switch (moveDir)
		{
			case MoveDir::FORWARD:
				advance(distance);
				break;
			case MoveDir::BACKWARD:
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

	void NavigationCamera::update(float deltaTime)
	{
		InputManager* inputManager = InputManager::getInstance();

		if (inputManager->getKey(Key::W_KEY))
			move(MoveDir::FORWARD, _movementSpeed * deltaTime);
		if (inputManager->getKey(Key::A_KEY))
			move(MoveDir::LEFT, _movementSpeed * deltaTime);
		if (inputManager->getKey(Key::S_KEY))
			move(MoveDir::BACKWARD, _movementSpeed * deltaTime);
		if (inputManager->getKey(Key::D_KEY))
			move(MoveDir::RIGHT, _movementSpeed * deltaTime);		
		if (inputManager->getKey(Key::Q_KEY))
			move(MoveDir::UP, _movementSpeed * deltaTime);
		if (inputManager->getKey(Key::E_KEY))
			move(MoveDir::DOWN, _movementSpeed * deltaTime);

		float horRotation = inputManager->getAxis(InputAxis::HORIZONTAL);
		float verRotation = inputManager->getAxis(InputAxis::VERTICAL);

		yaw(horRotation * _rotationSpeed * deltaTime);
		pitch(verRotation * _rotationSpeed * deltaTime);
	}
}