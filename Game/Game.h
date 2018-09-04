#pragma once

#include <iostream>
#include "GameBase.h"
using namespace std;

class Material;
class Triangle;

class Game : public GameBase
{
private:
	int _frame;
	Material* _material;
	Triangle* _triangle;

protected:
	bool onStart() override;
	bool onStop() override;
	bool onUpdate() override;
	bool onDraw() override;

public:
	Game();
	~Game();
};

