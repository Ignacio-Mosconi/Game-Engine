#pragma once
#include "Entity.h"

class Material;

class ENGINE_API Shape : public Entity
{
protected:
	Material * _material;
	float* _vertexBufferData;
	unsigned int _vertexBufferID;
	unsigned int _vertexCount;

public:
	Shape(Renderer* renderer, Material* material, unsigned int vertexCount);
	~Shape();

	bool create(float* vertexBufferData, unsigned int vertexComponents);
	bool dispose();

	void draw() const = 0;
};

