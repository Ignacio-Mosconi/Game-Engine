#pragma once

#include "Exports.h"

class ENGINE_API BoundingBox
{
private:
	float _width;
	float _height;

public:
	BoundingBox(float width, float height);
	~BoundingBox();

	void onCollision();

	inline float getWidth() const { return _width; }
	inline float getHeight() const { return _height;  }
};

