#include "Avatar.h"
#include "Sprite.h"
#include "BoundingBox.h"
#include "Material.h"

Avatar::Avatar(Sprite* sprite) : _sprite(sprite)
{
	float boundingBoxWidth = (float)(_sprite->getMaterial()->getTextureWidth());
	float boundingBoxHeight = (float)(_sprite->getMaterial()->getTextureHeight());

	_sprite->setPosition(0, 0, 0);
	_boundingBox = new BoundingBox(boundingBoxWidth, boundingBoxHeight);
}

Avatar::Avatar(Sprite* sprite, float x, float y) : _sprite(sprite)
{
	float boundingBoxWidth = (float)(_sprite->getMaterial()->getTextureWidth());
	float boundingBoxHeight = (float)(_sprite->getMaterial()->getTextureHeight());

	_sprite->setPosition(x, y, 0);
	_boundingBox = new BoundingBox(boundingBoxWidth, boundingBoxHeight);
}

Avatar::~Avatar()
{
}

vec2 Avatar::getSpritePosition() const
{
	return vec2(_sprite->getPosition().x, _sprite->getPosition().y);
}
