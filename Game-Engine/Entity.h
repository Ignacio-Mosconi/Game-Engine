#pragma once

#include <iostream>
#include "Exports.h"
using namespace std;

class Renderer;

class ENGINE_API Entity
{
protected:
	Renderer* _renderer;

public:
	Entity(Renderer* renderer);
	virtual ~Entity();

	virtual void draw() const;
};