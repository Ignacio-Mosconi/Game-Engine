#pragma once

#include <iostream>
#include "GameBase.h"
using namespace std;

class Material;
class Triangle;
class Rectangle;

class Game : public GameBase
{
private:
	int _frame;
	Material* _simpleMaterial;
	Material* _customMaterial;
	Triangle* _triangle;
	Rectangle* _rectangle;

protected:
	bool onStart() override;
	bool onStop() override;
	bool onUpdate() override;
	bool onDraw() override;

public:
	Game();
	~Game();
};

