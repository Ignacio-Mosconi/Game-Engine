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
	_gameEntity1 = new GameEntity(_renderer, imagePath, layerA, -4.0f, 0.0f);
	_gameEntity2 = new GameEntity(_renderer, imagePath, layerB, 4.0f, 0.0f);

	float rectangleColorData[] =
	{
		0.1f, 0.1f, 0.7f,
		0.5f, 0.1f, 0.5f,
		0.7f, 0.1f, 0.1f,
		0.7f, 0.7f, 0.2f
	};

	_triangle->create(3);
	_rectangle->create(3, rectangleColorData);
	_circle->create(3);
	_sprite->create(3);
	_sprite->setFramesInfo(2, 2, 256, 256);
	_sprite->setAnimationFrame(1);

	_triangle->setPosition(4, 0, 0);
	_rectangle->setPosition(-4, 0, 0);
	_circle->setPosition(0, 0, 0);
	_sprite->setPosition(0, 1, 0);
	_sprite->setScale(2, 2, 2);

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

	CollisionManager::deleteInstance();

	return true;
}

bool Game::onUpdate()
{
	cout << "Game::onUpdate()" << endl;

	_frame++;
	cout << "Frame: " << _frame << endl;

	float offset = 0.05f;

	_triangle->translate(offset, 0, 0);
	_triangle->rotate(0, 0, offset);
	
	_rectangle->translate(-offset, 0, 0);
	_rectangle->rotate(0, 0, -offset);

	_circle->translate(0, offset, 0);
	_circle->rotate(0, 0, -offset);

	_sprite->translate(0, -offset, 0);

	_gameEntity1->getSprite()->translate(offset, 0, 0);
	_gameEntity2->getSprite()->translate(-offset, 0, 0);

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