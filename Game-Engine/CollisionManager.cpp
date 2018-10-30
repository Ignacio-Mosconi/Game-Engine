#include "CollisionManager.h"
#include "Avatar.h"
#include "BoundingBox.h"

CollisionManager* CollisionManager::_instance = getInstance();

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

CollisionManager* CollisionManager::getInstance()
{
	if (!_instance)
		_instance = new CollisionManager;

	return _instance;
}

void CollisionManager::deleteInstance()
{
	if (_instance)
		delete _instance;
}

void CollisionManager::registerAvatar(Avatar* avatar, string layer)
{	
	_collisionLayers[layer].push_back(avatar);
}

void CollisionManager::update()
{
	map<string, vector<Avatar*>>::iterator mapItA;
	map<string, vector<Avatar*>>::iterator mapItB;
	vector<Avatar*>::iterator vecItA;
	vector<Avatar*>::iterator vecItB;
	
	for (mapItA = _collisionLayers.begin(); mapItA != _collisionLayers.end(); mapItA++)
	{
		for (vecItA = mapItA->second.begin(); vecItA != mapItA->second.end(); vecItA++)
		{
			vec2 posA((*vecItA)->getSpritePosition().x, (*vecItA)->getSpritePosition().y);
			float bbWidthA = (*vecItA)->getBoundingBox()->getWidth();
			float bbHeightA = (*vecItA)->getBoundingBox()->getHeight();

			for (mapItB = _collisionLayers.begin(); mapItB != _collisionLayers.end(); mapItB++)
			{
				if (mapItA->first != mapItB->first)
				{
					for (vecItB = mapItB->second.begin(); vecItB != mapItB->second.end(); vecItB++)
					{
						vec2 posB((*vecItB)->getSpritePosition().x, (*vecItB)->getSpritePosition().y);
						float bbWidthB = (*vecItB)->getBoundingBox()->getWidth();
						float bbHeightB = (*vecItB)->getBoundingBox()->getHeight();

						float minDistX = bbWidthA / 2 + bbWidthB / 2;
						float minDistY = bbHeightA / 2 + bbHeightB / 2;

						vec2 diff = posB - posA;
						float deltaX = abs(diff.x);
						float deltaY = abs(diff.y);

						if (deltaX < minDistX && deltaY < minDistY)
						{
							(*vecItA)->getBoundingBox()->onCollision();
							(*vecItB)->getBoundingBox()->onCollision();
						}
					}
				}
			}
		}
	}
}
