#include "Player.h"

using namespace gn;

Player::Player(Renderer* renderer, float movementSpeed) : Entity(renderer), _movementSpeed(movementSpeed)
{
	_fpsCamera = new Camera(renderer, _position, _rotation);
}

Player::Player(Renderer* renderer, float posX, float posY, float posZ, float movementSpeed) : 
Entity(renderer, glm::vec3(posX, posY, posZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 (1.0f, 1.0f, 1.0f)), 
_movementSpeed(movementSpeed)
{
	_fpsCamera = new Camera(renderer, _position, _rotation);
}

Player::~Player()
{
	delete _fpsCamera;
}

void Player::move(MoveDir moveDir, float distance)
{
	switch (moveDir)
	{
		case MoveDir::FORWARD:
			translate(0.0f, 0.0f, distance);
			_fpsCamera->advance(distance);
			break;
		case MoveDir::BACKWARD:
			translate(0.0f, 0.0f, -distance);
			_fpsCamera->advance(-distance);
			break;
		case MoveDir::LEFT:
			translate(-distance, 0.0f, 0.0f);
			_fpsCamera->strafe(-distance);
			break;
		case MoveDir::RIGHT:
			translate(distance, 0.0f, 0.0f);
			_fpsCamera->strafe(distance);
			break;
		default:
			break;
	}
}

void Player::moveCamera(glm::vec2 mousePosition)
{

}

void Player::update(float deltaTime)
{
	if (InputManager::getInstance()->getKey(Key::W_KEY))
		move(MoveDir::FORWARD, _movementSpeed * deltaTime);	
	if (InputManager::getInstance()->getKey(Key::A_KEY))
		move(MoveDir::LEFT, _movementSpeed * deltaTime);
	if (InputManager::getInstance()->getKey(Key::S_KEY))
		move(MoveDir::BACKWARD, _movementSpeed * deltaTime);
	if (InputManager::getInstance()->getKey(Key::D_KEY))
		move(MoveDir::RIGHT, _movementSpeed * deltaTime);
}

void Player::draw() const
{
	_renderer->loadIdentityMatrix();
	_renderer->setModelMatrix(_modelMatrix);
}