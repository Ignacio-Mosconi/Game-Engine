#pragma once

#include "Shape.h"

class ENGINE_API Sprite : public Shape
{
private:
	float* _uvBufferData;
	unsigned int _uvBufferID;
	unsigned int _frameID;
	unsigned int _rows;
	unsigned int _columns;
	unsigned int _frameWidth;
	unsigned int _frameHeight;

public:
	Sprite(Renderer* renderer, Material* material, float boundingBoxWidth, float boundingBoxHeight);
	~Sprite();

	bool create(unsigned int vertexComponents, float* colorBufferData = NULL) override;
	float* setVertices(unsigned int vertexComponents) const override;
	float* setVerticesUV(unsigned int x, unsigned int y) const;
	
	void setAnimationFrame(unsigned int id);
	void setFramesInfo(unsigned int rows, unsigned int columns, unsigned int frameWidth, unsigned int frameHeight);

	void draw() const override;
};