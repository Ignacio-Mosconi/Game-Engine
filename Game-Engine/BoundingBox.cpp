#include "BoundingBox.h"

BoundingBox::BoundingBox(float width, float height) : _width(width), _height(height)
{
}

BoundingBox::~BoundingBox()
{
}

void BoundingBox::onCollision()
{

}

vec2 BoundingBox::getEntityAttachedPosition() const
{
	return vec2(getEntityAttachedPosition().x, getEntityAttachedPosition().y);
}
