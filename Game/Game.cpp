#include "Game.h"

using namespace gn;

Game::Game() : GameBase()
{
	timer = 0.0f;
}

Game::~Game()
{
}

bool Game::onStart()
{
	_customColorMaterial = Material::generateMaterial(CUSTOM_VERTEX_SHADER_PATH, CUSTOM_PIXEL_SHADER_PATH);	
	
	_cube = new Cube(_renderer, _customColorMaterial);
	_cube->create(3, NULL, 100.0f, 100.0f, 100.0f);
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

	delete _cube;
	
	Material::destroyMaterial(_customColorMaterial);
	
	return true;
}

bool Game::onUpdate(float deltaTime)
{	
	timer += deltaTime;;

	float radius = 300.0f;

	float camX = glm::sin(timer) * radius;
	float camZ = glm::cos(timer) * radius;

	_renderer->updateView(glm::vec3(camX, -300.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	return true;
}

bool Game::onDraw()
{
	_cube->draw();

	return true;
}