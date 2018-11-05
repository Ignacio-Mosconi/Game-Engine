#pragma once

#include "Shape.h"

class ENGINE_API Rectangle : public Shape
{
public:
	Rectangle(Renderer* renderer, Material* material);
	~Rectangle();

	float* setVertices(unsigned int vertexComponents, float width = 1.0f, float height = 1.0f) const override;

	void draw() const override;
};