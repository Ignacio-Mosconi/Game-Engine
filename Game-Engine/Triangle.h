#pragma once

#include "Exports.h"
#include "Shape.h"

class ENGINE_API Triangle : public Shape
{
public:
	Triangle(Renderer* renderer, Material* material);
	~Triangle();

	void draw() const override;
};