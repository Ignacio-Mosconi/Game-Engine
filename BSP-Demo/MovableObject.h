#pragma once

#include "Core/InputManager.h"
#include "Scene Graph/Transform.h"

using namespace gn;

class MovableObject
{
private:
	Transform* _objectTransform;
	float _speed;

public:
	MovableObject(Transform* objectTransform, float speed = 5.0f);
	~MovableObject();

	void update(float deltaTime);
};
