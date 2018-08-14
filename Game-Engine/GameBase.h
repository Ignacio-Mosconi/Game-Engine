#pragma once

#include <iostream>
#include "Exports.h"
using namespace std;

class Renderer;

class ENGINE_API GameBase
{
protected:
	Renderer* _renderer;
	virtual bool onStart() = 0;
	virtual bool onStop() = 0;
	virtual bool onUpdate() = 0;

public:
	GameBase();
	~GameBase();

	bool start();
	bool stop();
	void run();
};

