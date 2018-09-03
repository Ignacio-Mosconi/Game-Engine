#pragma once

#include "Exports.h"
#include "Entity.h"

class ENGINE_API Triangle : public Entity
{
private:
	float* _vertexBufferData;
	unsigned int _vertexBufferID;
	int _vertexCount;

public:
	Triangle(Renderer* renderer);
	~Triangle();

	void create(float* vertexBufferData, int vertexCount, int vertexComponents);
	void dispose();

	void draw() const override;
};