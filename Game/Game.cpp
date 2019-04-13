#include "Game.h"

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

	_simpleColorMaterial = Material::generateMaterial(SIMPLE_VERTEX_SHADER_PATH, SIMPLE_PIXEL_SHADER_PATH);
	_customColorMaterial = Material::generateMaterial(CUSTOM_VERTEX_SHADER_PATH, CUSTOM_PIXEL_SHADER_PATH);

	_navCamera = new NavigationCamera(_renderer, 0.0f, 0.0f, 10.0f);
	
	_cube = new Cube(_renderer, _customColorMaterial);
	_cube->create(3, NULL, 2.0f, 2.0f, 2.0f);
	_cube->setPosition(0.0f, 0.0f, 0.0f);

	float frontColor[4] = { 0.0f, 1.0f, 0.0f};
	float backColor[4] = { 0.0f, 0.0f, 1.0f };

	_cube->setFaceColors(frontColor, backColor);
	
	return true;
}

bool Game::onStop()
{
	_cube->dispose();

	delete _navCamera;
	delete _cube;
	
	InputManager::deleteInstance();
	Material::destroyMaterial(_simpleColorMaterial);
	Material::destroyMaterial(_customColorMaterial);
	
	return true;
}

bool Game::onUpdate(float deltaTime)
{	
	_navCamera->update(deltaTime);

	_cube->rotate(3.0f * deltaTime, 3.0f * deltaTime, 3.0f * deltaTime);

	return true;
}

bool Game::onDraw()
{
	_cube->draw();

	return true;
}