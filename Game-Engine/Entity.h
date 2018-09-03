#pragma once

#include "Exports.h"

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