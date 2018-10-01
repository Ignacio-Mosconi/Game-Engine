#pragma once

#include <iostream>
#include <glm.hpp>
#include <gtc\constants.hpp>
#include "GameBase.h"
using namespace glm;
using namespace std;

class Material;
class Triangle;
class Rectangle;
class Circle;

class Game : public GameBase
{
private:
	int _frame;
	Material* _simpleMaterial;
	Material* _customMaterial;
	Triangle* _triangle;
	Rectangle* _rectangle;
	Circle* _circle;

protected:
	bool onStart() override;
	bool onStop() override;
	bool onUpdate() override;
	bool onDraw() override;

public:
	Game();
	~Game();
};

