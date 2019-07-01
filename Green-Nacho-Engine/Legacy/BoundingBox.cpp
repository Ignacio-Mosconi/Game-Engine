#include "Legacy/BoundingBox.h"
#include "Legacy/Entity.h"
#include "Legacy/GameEntity2D.h"

namespace gn
{
	namespace legacy
	{
		BoundingBox::BoundingBox(float width, float height, bool staticObject, float mass) :
			_entityAttached(NULL), _gameEntityAttached(NULL),
			_width(width), _height(height), _staticObject(staticObject), _mass(mass)
		{
		}

		BoundingBox::~BoundingBox()
		{
		}

		void BoundingBox::attachToEntity(Entity* entity)
		{
			_entityAttached = entity;
		}

		void BoundingBox::attachToGameEntity(GameEntity2D* gameEntity)
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
						case CollisionDir::LEFT:
							if (_gameEntityAttached)
								_gameEntityAttached->move(-penetration, 0, 0);
							else
								_entityAttached->translate(-penetration, 0, 0);
							break;
						case CollisionDir::RIGHT:
							if (_gameEntityAttached)
								_gameEntityAttached->move(penetration, 0, 0);
							else
								_entityAttached->translate(penetration, 0, 0);
							break;
						case CollisionDir::UP:
							if (_gameEntityAttached)
								_gameEntityAttached->move(0, penetration, 0);
							else
								_entityAttached->translate(0, penetration, 0);
							break;
						case CollisionDir::DOWN:
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
						case CollisionDir::LEFT:
							if (_gameEntityAttached)
								_gameEntityAttached->move(-penetration * penetrationMult, 0, 0);
							else
								_entityAttached->translate(-penetration * penetrationMult, 0, 0);
							break;
						case CollisionDir::RIGHT:
							if (_gameEntityAttached)
								_gameEntityAttached->move(penetration * penetrationMult, 0, 0);
							else
								_entityAttached->translate(penetration * penetrationMult, 0, 0);
							break;
						case CollisionDir::UP:
							if (_gameEntityAttached)
								_gameEntityAttached->move(0, penetration * penetrationMult, 0);
							else
								_entityAttached->translate(0, penetration * penetrationMult, 0);
							break;
						case CollisionDir::DOWN:
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

		glm::vec3 BoundingBox::getEntityAttachedPosition() const
		{
			return _entityAttached->getPosition();
		}
	}
}