#pragma once

#include "Entity.h"
#include "Camera.h"
#include "Renderer.h"
#include "InputManager.h"
#include "Enums.h"

enum class MoveDir
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Player : gn::Entity
{
private:
	gn::Camera* _fpsCamera;
	float _movementSpeed;

	void move(MoveDir moveDir, float distance);

public:
	Player(gn::Renderer* renderer, float movementSpeed = 2.0f);
	Player(gn::Renderer* renderer, float posX, float posY, float posZ, float movementSpeed = 2.0f);
	~Player();

	void update(float deltaTime);
	void draw() const override;
};