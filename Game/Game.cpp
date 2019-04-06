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
	_simpleMaterial = Material::generateMaterial(SIMPLE_VERTEX_SHADER_PATH, SIMPLE_PIXEL_SHADER_PATH);	
	
	_cube = new Cube(_renderer, _simpleMaterial);
	_cube->create(3, NULL, 100.0f, 100.0f, 100.0f);
	_cube->setPosition(0.0f, 0.0f, 0.0f);

	_renderer->updateView(glm::vec3(400.0f, 300.0f, 300.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	
	return true;
}

bool Game::onStop()
{
	_cube->dispose();

	delete _cube;
	
	Material::destroyMaterial(_simpleMaterial);
	
	return true;
}

bool Game::onUpdate(float deltaTime)
{	
	return true;
}

bool Game::onDraw()
{
	_cube->draw();

	return true;
}