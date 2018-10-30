#pragma once

#include <glm.hpp>
#include "Exports.h"

using namespace glm;

class Entity;

class ENGINE_API BoundingBox
{
private:
	Entity* _entityAttached;
	float _width;
	float _height;

public:
	BoundingBox(float width, float height);
	~BoundingBox();

	void onCollision();

	inline vec2 getEntityAttachedPosition() const;
	inline float getWidth() const { return _width; }
	inline float getHeight() const { return _height; }

	void setWidth(float width) { _width = width; }
	void setHeight(float height) { _height = _height; }
};

