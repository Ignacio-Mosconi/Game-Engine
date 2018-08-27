#pragma once

#include <iostream>
#include <string>
#include "Exports.h"
using namespace std;

class ENGINE_API Window
{
private:
	int _width;
	int _height;
	string _title;

public:
	Window();
	~Window();

	bool start(const int& width, const int& height, const char* title);
	bool stop();
};