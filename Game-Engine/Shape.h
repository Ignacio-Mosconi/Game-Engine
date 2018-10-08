#pragma once
#include "Entity.h"

class Material;

class ENGINE_API Shape : public Entity
{
protected:
	Material* _material;
	float* _vertexBufferData;
	float* _colorBufferData;
	float* _uvBufferData;
	unsigned int _vertexBufferID;
	unsigned int _colorBufferID;
	unsigned int _uvBufferID;
	unsigned int _vertexCount;

public:
	Shape(Renderer* renderer, Material* material, unsigned int vertexCount);
	~Shape();

	bool create(unsigned int vertexComponents, float* colorBufferData = NULL, float* uvBufferData = NULL);
	virtual float* setVertices(unsigned int vertexComponents) const = 0;
	virtual float* setVerticesColor(float* colorBufferData, unsigned int vertexComponents) const;
	virtual float* setVerticesUV(float* uvBufferData) const;
	bool dispose();

	void draw() const;
};