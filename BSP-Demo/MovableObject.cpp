#include "MovableObject.h"

MovableObject::MovableObject(Transform* objectTransform, float speed) : _objectTransform(objectTransform), _speed(speed)
{

}

MovableObject::~MovableObject()
{

}

void MovableObject::update(float deltaTime)
{
	float translateX = 0.0f;
	float translateZ = 0.0f;

	if (InputManager::getInstance()->getKey(Key::LEFT))
		translateX -= _speed * deltaTime;	
	if (InputManager::getInstance()->getKey(Key::RIGHT))
		translateX += _speed * deltaTime;	
	if (InputManager::getInstance()->getKey(Key::UP))
		translateZ -= _speed * deltaTime;	
	if (InputManager::getInstance()->getKey(Key::DOWN))
		translateZ += _speed * deltaTime;

	_objectTransform->translate(translateX, 0.0f, translateZ);
}