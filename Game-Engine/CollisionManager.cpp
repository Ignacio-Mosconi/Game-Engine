#include "CollisionManager.h"
#include "Entity.h"

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

void CollisionManager::registerEntity(Entity* entity, string collisionLayer)
{	
	collisionLayers[collisionLayer].push_back(entity);
}

void CollisionManager::update()
{
	map<string, vector<Entity*>>::iterator mapItA;
	map<string, vector<Entity*>>::iterator mapItB;
	vector<Entity*>::iterator vecItA;
	vector<Entity*>::iterator vecItB;
	
	for (mapItA = collisionLayers.begin(); mapItA != collisionLayers.end(); mapItA++)
	{
		for (vecItA = mapItA->second.begin(); vecItA != mapItA->second.end(); vecItA++)
		{
			vec2 posA((*vecItA)->getPosition().x, (*vecItA)->getPosition().y);
			float bbWidthA = (*vecItA)->getBoundBoxWidth();
			float bbHeightA = (*vecItA)->getBoundBoxHeight();

			for (mapItB = collisionLayers.begin(); mapItB != collisionLayers.end(); mapItB++)
			{
				if (mapItA->first != mapItB->first)
				{
					for (vecItB = mapItB->second.begin(); vecItB != mapItB->second.end(); vecItB++)
					{
						vec2 posB((*vecItB)->getPosition().x, (*vecItB)->getPosition().y);
						float bbWidthB = (*vecItB)->getBoundBoxWidth();
						float bbHeightB = (*vecItB)->getBoundBoxHeight();

						float minDistX = bbWidthA / 2 + bbWidthB / 2;
						float minDistY = bbHeightA / 2 + bbHeightB / 2;

						vec2 diff = posB - posA;
						float deltaX = abs(diff.x);
						float deltaY = abs(diff.y);

						if (deltaX < minDistX && deltaY < minDistY)
						{

						}
					}
				}
			}
		}
	}
}
