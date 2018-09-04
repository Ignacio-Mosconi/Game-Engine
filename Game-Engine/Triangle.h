#pragma once

#include "Exports.h"
#include "Entity.h"

class Material;

class ENGINE_API Triangle : public Entity
{
private:
	Material* _material;
	float* _vertexBufferData;
	unsigned int _vertexBufferID;
	int _vertexCount;

public:
	Triangle(Renderer* renderer, Material* material);
	~Triangle();

	bool create(float* vertexBufferData, int vertexCount, int vertexComponents);
	bool dispose();

	void draw() const override;
};