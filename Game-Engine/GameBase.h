#pragma once

#include <iostream>
#include "Exports.h"

using namespace std;

class Window;
class Renderer;

/*
The base class of the game; the "Game" class has to be a child of it.
It implements the basic functionality of the game.
*/

class ENGINE_API GameBase
{
private:
	double _lastTime;

protected:
	Window* _window;
	Renderer* _renderer;
	
	virtual bool onStart() = 0;
	virtual bool onStop() = 0;
	virtual bool onUpdate(float deltaTime) = 0;
	virtual bool onDraw() = 0;

public:
	GameBase();
	~GameBase();

	bool start(const int& width, const int& height, const char* title);
	bool stop();
	void run();
};