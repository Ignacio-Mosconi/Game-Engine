#pragma once

#include <iostream>
#include "Exports.h"
using namespace std;

class ENGINE_API Renderer
{
public:
	Renderer();
	~Renderer();

	bool start();
	bool stop();
};

