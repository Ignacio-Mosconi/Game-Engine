#include "BoundingBox.h"

BoundingBox::BoundingBox(float width, float height, bool staticObject, float mass) :
_entityAttached(NULL), _width(width), _height(height), _staticObject(staticObject), _mass(mass)
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

void BoundingBox::onCollision(BoundingBox* collider, float penetration, CollisionDir direction)
{
	cout << "BoundingBox::onCollision()" << endl;
	
	if (!_staticObject)
	{
		if (collider->isStatic())
		{
			switch (direction)
			{
				case Left:
					_entityAttached->translate(-penetration, 0, 0);
					break;
				case Right:
					_entityAttached->translate(penetration, 0, 0);
					break;
				case Up:
					_entityAttached->translate(0, penetration, 0);
					break;
				case Down:
					_entityAttached->translate(0, -penetration, 0);
					break;
			}
		}
		else
		{
			float massRatio = _mass / collider->getMass();
			float penetrationMult = 1.0f / (1.0f + massRatio);

			switch (direction)
			{
			case Left:
				_entityAttached->translate(-penetration * penetrationMult, 0, 0);
				break;
			case Right:
				_entityAttached->translate(penetration * penetrationMult, 0, 0);
				break;
			case Up:
				_entityAttached->translate(0, penetration * penetrationMult, 0);
				break;
			case Down:
				_entityAttached->translate(0, -penetration * penetrationMult, 0);
				break;
			}
		}
	}
}

void BoundingBox::setPhysicalProperties(bool staticObject, float mass)
{
	cout << "BoundingBox::setPhysicalProperties(staticObject, mass)" << endl;

	_staticObject = staticObject;
	_mass = mass;
}
