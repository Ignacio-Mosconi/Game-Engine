#include "BoundingBox.h"
#include "GameEntity.h"

BoundingBox::BoundingBox(float width, float height, bool staticObject, float mass) :
_entityAttached(NULL), _gameEntityAttached(NULL),
_width(width), _height(height), _staticObject(staticObject), _mass(mass)
{
	cout << "BoundingBox::BoundingBox()" << endl;
}

BoundingBox::~BoundingBox()
{
	cout << "BoundingBox::~BoundingBox()" << endl;
}

void BoundingBox::attachToEntity(Entity* entity)
{
	_entityAttached = entity;
}

void BoundingBox::attachToGameEntity(GameEntity* gameEntity)
{
	_gameEntityAttached = gameEntity;
	_entityAttached = (Entity*)gameEntity->getSprite();
}

void BoundingBox::onCollision(BoundingBox* collider, float penetration, CollisionDir direction)
{	
	if (!_staticObject)
	{
		if (collider->isStatic())
		{
			switch (direction)
			{
				case Left:
					if (_gameEntityAttached)
						_gameEntityAttached->move(-penetration, 0, 0);
					else
						_entityAttached->translate(-penetration, 0, 0);
					break;
				case Right:
					if (_gameEntityAttached)
						_gameEntityAttached->move(penetration, 0, 0);
					else
						_entityAttached->translate(penetration, 0, 0);
					break;
				case Up:
					if (_gameEntityAttached)
						_gameEntityAttached->move(0, penetration, 0);
					else
						_entityAttached->translate(0, penetration, 0);
					break;
				case Down:
					if (_gameEntityAttached)
						_gameEntityAttached->move(0, -penetration, 0);
					else
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
					if (_gameEntityAttached)
						_gameEntityAttached->move(-penetration * penetrationMult, 0, 0);
					else
						_entityAttached->translate(-penetration * penetrationMult, 0, 0);
					break;
				case Right:
					if (_gameEntityAttached)
						_gameEntityAttached->move(penetration * penetrationMult, 0, 0);
					else
						_entityAttached->translate(penetration * penetrationMult, 0, 0);
					break;
				case Up:
					if (_gameEntityAttached)
						_gameEntityAttached->move(0, penetration * penetrationMult, 0);
					else
						_entityAttached->translate(0, penetration * penetrationMult, 0);
					break;
				case Down:
					if (_gameEntityAttached)
						_gameEntityAttached->move(0, -penetration * penetrationMult, 0);
					else
						_entityAttached->translate(0, -penetration * penetrationMult, 0);
					break;
			}
		}
	}
}

void BoundingBox::setPhysicalProperties(bool staticObject, float mass)
{
	_staticObject = staticObject;
	_mass = mass;
}