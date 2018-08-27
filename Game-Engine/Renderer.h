#pragma once

#include <iostream>
#include "Exports.h"
using namespace std;

class Window;

class ENGINE_API Renderer
{
private:
	Window* _renderWindow;

public:
	Renderer();
	~Renderer();

	bool start(Window* renderWindow);
	bool stop();
	void setClearColor(float r, float g, float b, float a);
	void clearScreen();
	void swapBuffers();
};

