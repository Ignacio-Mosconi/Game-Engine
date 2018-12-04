#pragma once

#include "GameEntity.h"
#include "Renderer.h"
#include "Tilemap.h"
#include "Animation.h"
#include "InputManager.h"

enum MoveDirection
{
	Left, Right
};

class Player : public gn::GameEntity
{
private:
	gn::Animation* _idleRightAnimation;
	gn::Animation* _idleLeftAnimation;
	gn::Animation* _walkRightAnimation;
	gn::Animation* _walkLeftAnimation;

	MoveDirection _facing;
	float _movementSpeed;

public:
	Player(gn::Renderer* renderer, gn::Tilemap* tilemap, const std::string& imagePath, const std::string& collisionLayer,
		float x, float y, int spriteRows, int spriteColumns, int frameWidth, int frameHeight,
		float mass = 1.0f, float movementSpeed = 200.0f);
	
	virtual ~Player();

	void update(float deltaTime) override;
	void draw() const override;

	void move(MoveDirection moveDirection, float amount);
};