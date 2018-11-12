#include "Definitions.h"
#include "Game.h"
#include "Material.h"
#include "Texture.h"
#include "Entity.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Sprite.h"
#include "GameEntity.h"
#include "CollisionManager.h"

Game::Game() : GameBase()
{
	cout << "Game::Game()" << endl;
}

Game::~Game()
{
	cout << "Game::~Game()" << endl;
}

bool Game::onStart()
{
	cout << "Game::onStart()" << endl;

	_frame = 0;

	_simpleMaterial = Material::generateMaterial(SIMPLE_VERTEX_SHADER_PATH, SIMPLE_PIXEL_SHADER_PATH);
	_customMaterial = Material::generateMaterial(CUSTOM_VERTEX_SHADER_PATH, CUSTOM_PIXEL_SHADER_PATH);
	_textureMaterial = Material::generateMaterial(TEXTURE_VERTEX_SHADER_PATH, TEXTURE_PIXEL_SHADER_PATH);
	
	_texture = Texture::generateTextureBMP(SPRITE_SHEET_TEXTURE_PATH);
	_textureMaterial->setTexture(_texture, "textureSampler");

	_triangle = new Triangle(_renderer, _simpleMaterial);
	_rectangle = new Rectangle(_renderer, _customMaterial);
	_circle = new Circle(_renderer, _simpleMaterial, 20);
	_sprite = new Sprite(_renderer, _textureMaterial);

	string imagePath(SPRITE_SHEET_TEXTURE_PATH);
	string layerA("Group A");
	string layerB("Group B");
	_gameEntity1 = new GameEntity(_renderer, imagePath, layerA, 128, 500, 2, 2, 256, 256, false, 2.0f);
	_gameEntity2 = new GameEntity(_renderer, imagePath, layerB, 1152, 500, 2, 2, 256, 256, false, 4.0f);

	float rectangleColorData[] =
	{
		0.1f, 0.1f, 0.7f,
		0.5f, 0.1f, 0.5f,
		0.7f, 0.1f, 0.1f,
		0.7f, 0.7f, 0.2f
	};

	_triangle->create(3, NULL, 100, 100);
	_rectangle->create(3, rectangleColorData, 200, 200);
	_circle->create(3, NULL, 75);
	_sprite->create(3, NULL, 256, 256);
	_sprite->setFramesInfo(2, 2, 256, 256);
	_sprite->setAnimationFrame(1);

	_triangle->setPosition(200, 600, 0);
	_rectangle->setPosition(300, 500, 0);
	_circle->setPosition(600, 400, 0);
	_sprite->setPosition(128, 128, 0);

	return true;
}

bool Game::onStop()
{
	cout << "Game::onStop()" << endl;

	_triangle->dispose();
	_rectangle->dispose();
	_circle->dispose();
	_sprite->dispose();
	
	delete _triangle;
	delete _rectangle;
	delete _circle;
	delete _sprite;

	delete _gameEntity1;
	delete _gameEntity2;

	Material::destroyMaterial(_simpleMaterial);
	Material::destroyMaterial(_customMaterial);
	Material::destroyMaterial(_textureMaterial);
	
	Texture::destroyTexture(_texture);
	GameEntity::destroyTextureMaterial();

	CollisionManager::deleteInstance();

	return true;
}

bool Game::onUpdate(float deltaTime)
{
	cout << "Game::onUpdate()" << endl;

	_frame++;
	cout << "Frame: " << _frame << endl;

	float offset = 25.0f;

	_triangle->translate(offset * deltaTime, 0, 0);
	_triangle->rotate(0, 0, offset * deltaTime);
	
	_rectangle->translate(-offset * deltaTime, 0, 0);
	_rectangle->rotate(0, 0, -offset * deltaTime);

	_circle->translate(0, offset * deltaTime, 0);
	_circle->rotate(0, 0, -offset * deltaTime);

	_gameEntity1->getSprite()->translate(offset * deltaTime, 0, 0);
	_gameEntity2->getSprite()->translate(-offset * deltaTime, 0, 0);

	CollisionManager::getInstance()->update();
	
	return (_frame < MAX_FRAMES) ? true : false;
}

bool Game::onDraw()
{
	cout << "Game::onDraw()" << endl;

	_triangle->draw();
	_rectangle->draw();
	_circle->draw();
	_sprite->draw();

	_gameEntity1->draw();
	_gameEntity2->draw();

	return true;
}