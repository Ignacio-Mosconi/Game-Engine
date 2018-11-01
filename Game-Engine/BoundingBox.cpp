#include "BoundingBox.h"

BoundingBox::BoundingBox(float width, float height) : _entityAttached(NULL), _width(width), _height(height)
{
	cout << "BoundingBox::BoundingBox()" << endl;
}

BoundingBox::~BoundingBox()
{
	cout << "BoundingBox::~BoundingBox()" << endl;
}

void BoundingBox::attachToEntity(Entity* entity)
{
	cout << "BoundingBox::attachToEnitity()" << endl;

	_entityAttached = entity;
}

void BoundingBox::onCollision()
{
	cout << "BoundingBox::onCollision()" << endl;
}
