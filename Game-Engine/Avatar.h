#pragma once

#include <glm.hpp>
#include "Exports.h"

using namespace glm;

class Sprite;
class BoundingBox;

class ENGINE_API Avatar
{
private:
	Sprite* _sprite;
	BoundingBox* _boundingBox;

public:
	Avatar(Sprite* sprite);
	Avatar(Sprite* sprite, float x, float y);
	~Avatar();

	vec2 getSpritePosition() const;
	inline BoundingBox* getBoundingBox() const { return _boundingBox; }
};

