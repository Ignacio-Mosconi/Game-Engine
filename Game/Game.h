#pragma once

#include <iostream>
#include "GameBase.h"
#include "Window.h"
#include "Renderer.h"
#include "Material.h"
#include "Texture.h"
#include "Entity.h"
#include "Shape.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Sprite.h"
#include "GameEntity.h"
#include "Animation.h"
#include "Tilemap.h"
#include "CollisionManager.h"
#include "InputManager.h"
#include "Definitions.h"

class Player;

class Game : public gn::GameBase
{
private:
	gn::Material* _simpleMaterial;
	gn::Material* _customMaterial;
	gn::Material* _textureMaterial;

	gn::Texture* _texture;

	gn::Triangle* _triangle;
	gn::Rectangle* _rectangle;
	gn::Circle* _circle;
	gn::Sprite* _sprite;

	gn::GameEntity* _gameEntity1;

	gn::Animation* _gameEntity1Idle;

	gn::Tilemap* _tilemap;

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