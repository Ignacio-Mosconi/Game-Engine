#pragma once

#include <iostream>
#include "GameBase.h"

using namespace std;

class Material;
class Texture;
class Triangle;
class Rectangle;
class Circle;
class Sprite;
class GameEntity;
class Animation;
class Tilemap;
class Player;

class Game : public GameBase
{
private:
	Material* _simpleMaterial;
	Material* _customMaterial;
	Material* _textureMaterial;

	Texture* _texture;

	Triangle* _triangle;
	Rectangle* _rectangle;
	Circle* _circle;
	Sprite* _sprite;
	GameEntity* _gameEntity1;
	GameEntity* _gameEntity2;

	Animation* _gameEntity1Idle;
	Animation* _gameEntity2Walk;

	Tilemap* _tilemap;

	Player* _player;

	int _frame;

protected:
	bool onStart() override;
	bool onStop() override;
	bool onUpdate(float deltaTime) override;
	bool onDraw() override;

public:
	Game();
	~Game();
};