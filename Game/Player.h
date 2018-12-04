#pragma once

#include <iostream>
#include "GameEntity.h"

enum MoveDirection
{
	Left, Right
};

class Player : public GameEntity
{
private:
	Animation* _idleRightAnimation;
	Animation* _idleLeftAnimation;
	Animation* _walkRightAnimation;
	Animation* _walkLeftAnimation;

	MoveDirection _facing;
	float _movementSpeed;

public:
	Player(Renderer* renderer, Tilemap* tilemap, const string& imagePath, const string& collisionLayer,
		float x, float y, int spriteRows, int spriteColumns, int frameWidth, int frameHeight,
		float mass = 1.0f, float movementSpeed = 200.0f);
	
	virtual ~Player();

	void update(float deltaTime) override;
	void draw() const override;

	void move(MoveDirection moveDirection, float amount);
};