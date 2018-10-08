#pragma once

#include "Shape.h"

class Sprite : public Shape
{
public:
	Sprite(Renderer* renderer, Material* material);
	~Sprite();

	float* setVertices(unsigned int vertexComponents) const override;
	float* setVerticesUV(float* uvBufferData) const override;

	void draw() const override;
};