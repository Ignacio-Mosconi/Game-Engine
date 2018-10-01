#pragma once

#include "Shape.h"

class ENGINE_API Rectangle : public Shape
{
public:
	Rectangle(Renderer* renderer, Material* material);
	~Rectangle();

	void draw() const override;
};