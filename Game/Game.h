#pragma once

#include <iostream>
#include "GameBase.h"
using namespace std;

class Game : public GameBase
{
private:
	int _frame;

protected:
	bool onStart() override;
	bool onStop() override;
	bool onUpdate() override;

public:
	Game();
	~Game();
};

