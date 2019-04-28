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

	_spriteTexture = Texture::generateTextureBMP(SPRITE_PATH);
	_simpleColorMaterial = Material::generateMaterial(SIMPLE_VERTEX_SHADER_PATH, SIMPLE_PIXEL_SHADER_PATH);
	_customColorMaterial = Material::generateMaterial(CUSTOM_VERTEX_SHADER_PATH, CUSTOM_PIXEL_SHADER_PATH);
	_textureMaterial = Material::generateMaterial(TEXTURE_VERTEX_SHADER_PATH, TEXTURE_PIXEL_SHADER_PATH);

	_textureMaterial->setTexture(_spriteTexture, "textureSampler");

	_navCamera = new NavigationCamera(_renderer, 0.0f, 0.0f, 10.0f);
	
	_cube = new Cube(_renderer, _customColorMaterial, 2.0f, 2.0f, 2.0f);
	_rifle = new Model(_renderer, ASSAULT_RIFLE_PATH);

	float frontColor[3] = { 0.0f, 1.0f, 0.0f};
	float backColor[3] = { 0.0f, 0.0f, 1.0f };

	_cube->setFaceColors(frontColor, backColor);
	
	return true;
}

bool Game::onStop()
{
	delete _navCamera;
	delete _cube;
	delete _rifle;
	
	InputManager::deleteInstance();

	Texture::destroyTexture(_spriteTexture);
	Material::destroyMaterial(_simpleColorMaterial);
	Material::destroyMaterial(_customColorMaterial);
	Material::destroyMaterial(_textureMaterial);
	
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
	//_cube->draw();
	_rifle->draw();

	return true;
}