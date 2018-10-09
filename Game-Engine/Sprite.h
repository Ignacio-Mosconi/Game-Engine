#pragma once

#include "Shape.h"

class ENGINE_API Sprite : public Shape
{
private:
	float* _uvBufferData;
	unsigned int _uvBufferID;

public:
	Sprite(Renderer* renderer, Material* material);
	~Sprite();

	bool create(unsigned int vertexComponents, float* colorBufferData = NULL) override;
	float* setVertices(unsigned int vertexComponents) const override;
	float* setVerticesUV() const;

	void draw() const override;
};