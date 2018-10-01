#pragma once

#include "Exports.h"
#include "Shape.h"

class ENGINE_API Circle : public Shape
{
public:
	Circle(Renderer* renderer, Material* material, unsigned int vertexCount);
	~Circle();

	float* setVertices(unsigned int vertexComponents) const override;

	void draw() const override;
};
