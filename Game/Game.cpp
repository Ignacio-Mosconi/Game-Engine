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
	_camera = new Camera(_renderer, glm::vec3(0.0f, 0.0f, 300.0f));

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
	
	//_camera->roll(45.0f);
	
	return true;
}

bool Game::onStop()
{
	_cube->dispose();

	delete _cube;
	delete _camera;
	
	Material::destroyMaterial(_customColorMaterial);
	
	return true;
}

bool Game::onUpdate(float deltaTime)
{	
	timer += deltaTime;

	_cube->rotate(-3.0f * deltaTime, -3.0f * deltaTime, -3.0f * deltaTime);

	//_camera->advance(30.0f * deltaTime);
	//_camera->strafe(30.0f * deltaTime);
	//_camera->ascend(30.0f * deltaTime);

	//_camera->pitch(-30.0f * deltaTime);
	//_camera->yaw(30.0f * deltaTime);
	//_camera->roll(30.0f * deltaTime);

	return true;
}

bool Game::onDraw()
{
	_cube->draw();

	return true;
}