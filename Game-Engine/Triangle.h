#pragma once

#include "Exports.h"
#include "Shape.h"

class ENGINE_API Triangle : public Shape
{
public:
	Triangle(Renderer* renderer, Material* material, float boundingBoxWidth, float boundingBoxHeight);
	~Triangle();

	float* setVertices(unsigned int vertexComponents) const override;

	void draw() const override;
};