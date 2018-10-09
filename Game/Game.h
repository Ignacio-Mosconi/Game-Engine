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
	
	int _frame;

protected:
	bool onStart() override;
	bool onStop() override;
	bool onUpdate() override;
	bool onDraw() override;

public:
	Game();
	~Game();
};