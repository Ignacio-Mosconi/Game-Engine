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
#include "Animation.h"
#include "Tilemap.h"

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

	_gameEntity1 = new GameEntity(_renderer, SPRITE_SHEET_TEXTURE_PATH, "Layer A", 128, 360, 2, 2, 256, 256, false, 2.0f);
	_gameEntity2 = new GameEntity(_renderer, NINJA_TEXTURE_PATH, "Layer B", 1152, 360, 6, 6, 192, 288, false, 4.0f);

	_gameEntity1->setBoundingBoxDimensions(200.0f, 200.0f);
	_gameEntity2->setBoundingBoxDimensions(180.0f, 250.0f);

	unsigned int framesIdle[2] = { 0, 1 };
	unsigned int framesWalk[6] = { 23, 22, 21, 20, 19, 18 };

	_gameEntity1Idle = new Animation(framesIdle, 24.0f, true);
	_gameEntity2Walk = new Animation(framesWalk, 30.0f, true);

	_gameEntity1->addAnimation(_gameEntity1Idle, "Idle");
	_gameEntity2->addAnimation(_gameEntity2Walk, "Walking");

	_gameEntity1Idle->play();
	_gameEntity2Walk->play();

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

	_triangle->setPosition(200, 100, 0);
	_rectangle->setPosition(300, 100, 0);
	_circle->setPosition(600, 600, 0);
	_sprite->setPosition(1152, 128, 0);

	_tilemap = new Tilemap(_renderer, TILESET_TEXTURE_PATH, LEVEL_1_PATH, 3840, 720, 32, 32, 6, 6);
	_tilemap->updateVerticesUV();
	//_tilemap->setTileInfo(0, Background);
	//for (int i = 1; i < 6; i++)
	//	_tilemap->setTileInfo(i, Wall);	
	//for (int i = 6; i < 27; i++)
	//	_tilemap->setTileInfo(i, Background);
	//for (int i = 27; i < 31; i++)
	//	_tilemap->setTileInfo(i, Wall);

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

	delete _gameEntity1Idle;
	delete _gameEntity2Walk;

	delete _tilemap;

	Material::destroyMaterial(_simpleMaterial);
	Material::destroyMaterial(_customMaterial);
	Material::destroyMaterial(_textureMaterial);
	
	Texture::destroyTexture(_texture);

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

	_gameEntity1->update(deltaTime);
	_gameEntity2->update(deltaTime);

	CollisionManager::getInstance()->update();
	
	return (_frame < MAX_FRAMES) ? true : false;
}

bool Game::onDraw()
{
	cout << "Game::onDraw()" << endl;

	_tilemap->draw();

	_triangle->draw();
	_rectangle->draw();
	_circle->draw();
	_sprite->draw();

	_gameEntity1->draw();
	_gameEntity2->draw();

	return true;
}