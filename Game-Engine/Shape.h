#pragma once
#include "Entity.h"

class Material;

class ENGINE_API Shape : public Entity
{
protected:
	Material* _material;
	float* _vertexBufferData;
	float* _colorBufferData;
	unsigned int _vertexBufferID;
	unsigned int _colorBufferID;
	unsigned int _vertexCount;

public:
	Shape(Renderer* renderer, Material* material, unsigned int vertexCount);
	~Shape();

	virtual bool create(unsigned int vertexComponents, float* colorBufferData = NULL);
	virtual float* setVertices(unsigned int vertexComponents) const = 0;
	virtual float* setVerticesColor(float* colorBufferData, unsigned int vertexComponents) const;
	bool dispose();

	void draw() const;
};