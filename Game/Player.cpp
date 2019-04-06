#include "Player.h"

using namespace gn;

Player::Player(Renderer* renderer, Tilemap* tilemap, const std::string& imagePath, const std::string& collisionLayer,
	float x, float y, int spriteRows, int spriteColumns, int frameWidth, int frameHeight, float mass, float movementSpeed) :
GameEntity(renderer, tilemap, imagePath, collisionLayer, x, y, spriteRows, spriteColumns, frameWidth, frameHeight, false, mass),
_facing(Right), _movementSpeed(movementSpeed)
{
	setBoundingBoxDimensions(90.0f, 125.0f);

	unsigned int framesIdleR[6] = { 0, 1, 2, 3, 4, 5 };
	unsigned int framesIdleL[6] = { 6, 7, 8, 9, 10, 11 };
	unsigned int framesWalkR[6] = { 12, 13, 14, 15, 16, 17 };
	unsigned int framesWalkL[6] = { 18, 19, 20, 21, 22, 23 };

	_idleRightAnimation = new Animation("Idle Right", framesIdleR, 3.0f, true);
	_idleLeftAnimation = new Animation("Idle Left", framesIdleL, 3.0f, true);
	_walkRightAnimation = new Animation("Walk Right", framesWalkR, 6.0f, true);
	_walkLeftAnimation = new Animation("Walk Left", framesWalkL, 6.0f, true);

	addAnimation(_idleRightAnimation, _idleRightAnimation->getName());
	addAnimation(_idleLeftAnimation, _idleLeftAnimation->getName());
	addAnimation(_walkRightAnimation, _walkRightAnimation->getName());
	addAnimation(_walkLeftAnimation, _walkLeftAnimation->getName());

	_idleRightAnimation->play();
}

Player::~Player()
{
	delete _idleRightAnimation;
	delete _walkRightAnimation;
	delete _walkLeftAnimation;
	delete _idleLeftAnimation;
}

void Player::update(float deltaTime)
{
	GameEntity::update(deltaTime);

	Animation* currAnim = getCurrentAnimation();

	if (InputManager::getInstance()->getKey(LeftKey) || InputManager::getInstance()->getKey(RightKey))
	{
		if (InputManager::getInstance()->getKey(LeftKey))
			move(Left, _movementSpeed * deltaTime);
		if (InputManager::getInstance()->getKey(RightKey))
			move(Right, _movementSpeed * deltaTime);
	}
	else
	{
		if (_facing == LeftCollision)
		{
			if (currAnim->getName() != _idleLeftAnimation->getName())
			{
				currAnim->stop();
				_idleLeftAnimation->play();
			}
		}
		else
		{
			if (currAnim->getName() != _idleRightAnimation->getName())
			{
				currAnim->stop();
				_idleRightAnimation->play();
			}
		}
	}
}

void Player::move(MoveDirection moveDirection, float amount)
{
	Animation* currentAnim = getCurrentAnimation();

	_facing = moveDirection;

	switch (moveDirection)
	{
		case LeftCollision:		
			if (currentAnim->getName() != _walkLeftAnimation->getName())
			{
				currentAnim->stop();	
				_walkLeftAnimation->play();
			}
			GameEntity::move(-amount, 0.0f);
			break;

		case RightCollision: 
			if (currentAnim->getName() != _walkRightAnimation->getName())
			{
				currentAnim->stop();
				_walkRightAnimation->play();
			}
			GameEntity::move(amount, 0.0f);
			break;
	}
}

void Player::draw() const
{
	GameEntity::draw();
}