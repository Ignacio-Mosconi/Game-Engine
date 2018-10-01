#pragma once

#include "Exports.h"
#include "Shape.h"

class ENGINE_API Circle : public Shape
{
public:
	Circle(Renderer* renderer, Material* material, unsigned int vertexCount);
	~Circle();

	void draw() const override;
};
