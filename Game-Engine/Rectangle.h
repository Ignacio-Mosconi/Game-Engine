#pragma once

#include "Shape.h"

class ENGINE_API Rectangle : public Shape
{
public:
	Rectangle(Renderer* renderer, Material* material);
	~Rectangle();

	float* setVertices(unsigned int vertexComponents) const override;

	void draw() const override;
};