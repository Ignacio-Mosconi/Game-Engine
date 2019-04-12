#include "Game.h"
#include "Player.h"

using namespace gn;

Game::Game() : GameBase()
{

}

Game::~Game()
{

}

bool Game::onStart()
{
	_inputManager = InputManager::getInstance();
	_inputManager->attachToWindow(_window);

	_customColorMaterial = Material::generateMaterial(CUSTOM_VERTEX_SHADER_PATH, CUSTOM_PIXEL_SHADER_PATH);	

	_player = new Player(_renderer, 0.0f, 0.0f, 10.0f, 5.0f);
	
	_cube = new Cube(_renderer, _customColorMaterial);
	_cube->create(3, NULL, 2.0f, 2.0f, 2.0f);
	_cube->setPosition(0.0f, 0.0f, 0.0f);

	float frontColor[3] = { 0.0f, 1.0f, 0.0f };
	float backColor[3] = { 1.0f, 0.0f, 0.0f };
	float leftColor[3] = { 0.0f, 0.0f, 1.0f };
	float rightColor[3] = { 1.0f, 0.0f, 1.0f };
	float bottomColor[3] = { 1.0f, 1.0f, 1.0f };
	float topColor[3] = { 1.0f, 1.0f, 0.0f };
	
	_cube->setFaceColors(frontColor, backColor, leftColor, rightColor, bottomColor, topColor);
	
	return true;
}

bool Game::onStop()
{
	_cube->dispose();

	delete _player;
	delete _cube;
	
	InputManager::deleteInstance();
	Material::destroyMaterial(_customColorMaterial);
	
	return true;
}

bool Game::onUpdate(float deltaTime)
{	
	_player->update(deltaTime);

	//_cube->rotate(3.0f * deltaTime, 3.0f * deltaTime, 3.0f * deltaTime);

	return true;
}

bool Game::onDraw()
{
	_player->draw();
	_cube->draw();

	return true;
}