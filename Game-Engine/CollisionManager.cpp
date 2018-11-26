#include "CollisionManager.h"
#include "Entity.h"
#include "BoundingBox.h"

CollisionManager* CollisionManager::_instance = NULL;

CollisionManager::CollisionManager()
{
	cout << "CollisionManager::CollisionManager()" << endl;
}

CollisionManager::~CollisionManager()
{
	cout << "CollisionManager::~CollisionManager()" << endl;
}

CollisionManager* CollisionManager::getInstance()
{
	cout << "CollisionManager::getInstance()" << endl;

	if (!_instance)
		_instance = new CollisionManager;

	return _instance;
}

void CollisionManager::deleteInstance()
{
	cout << "CollisionManager::deleteInstance()" << endl;

	if (_instance)
		delete _instance;
}

void CollisionManager::registerBoundingBox(BoundingBox* box, const string& layer)
{	
	cout << "CollisionManager::registerBoundingBox(box, layer)" << endl;

	_collisionLayers[layer].push_back(box);
}

bool CollisionManager::deregisterBoundingBox(BoundingBox* box)
{	
	cout << "CollisionManager::deregisterBoundingBox(box, layer)" << endl;

	bool wasDeregistered = false;

	map<string, vector<BoundingBox*>>::iterator mapIt;
	vector<BoundingBox*>::iterator vecIt;

	for (mapIt = _collisionLayers.begin(); mapIt != _collisionLayers.end(); mapIt++)
	{
		for (vecIt = mapIt->second.begin(); vecIt != mapIt->second.end(); vecIt++)
			if (*vecIt == box)
			{
				mapIt->second.erase(vecIt);
				wasDeregistered = true;
				break;
			}
		if (wasDeregistered)
			break;
	}	

	return wasDeregistered;
}

void CollisionManager::update()
{
	cout << "CollisionManager::update()" << endl;

	map<string, vector<BoundingBox*>>::iterator mapItA;
	map<string, vector<BoundingBox*>>::iterator mapItB;
	vector<BoundingBox*>::iterator vecItA;
	vector<BoundingBox*>::iterator vecItB;
	
	for (mapItA = _collisionLayers.begin(); mapItA != _collisionLayers.end(); mapItA++)
	{
		for (vecItA = mapItA->second.begin(); vecItA != mapItA->second.end(); vecItA++)
		{
			vec2 posA((*vecItA)->getEntityAttachedPosition().x, (*vecItA)->getEntityAttachedPosition().y);
			float bbWidthA = (*vecItA)->getWidth();
			float bbHeightA = (*vecItA)->getHeight();

			for (mapItB = _collisionLayers.begin(); mapItB != _collisionLayers.end(); mapItB++)
			{
				if (mapItA->first != mapItB->first)
				{
					for (vecItB = mapItB->second.begin(); vecItB != mapItB->second.end(); vecItB++)
					{
						vec2 posB((*vecItB)->getEntityAttachedPosition().x, (*vecItB)->getEntityAttachedPosition().y);
						float bbWidthB = (*vecItB)->getWidth();
						float bbHeightB = (*vecItB)->getHeight();

						float minDistX = (bbWidthA + bbWidthB) / 2;
						float minDistY = (bbHeightA + bbHeightB) / 2;

						vec2 diff = posB - posA;
						float deltaX = abs(diff.x);
						float deltaY = abs(diff.y);

						if (deltaX < minDistX && deltaY < minDistY)
						{
							CollisionDir boxADir;
							CollisionDir boxBDir;
							float horPenetration = minDistX - deltaX;
							float verPenetration = minDistY - deltaY;
							
							if (horPenetration > verPenetration)
							{
								if (diff.y > 0)
								{
									boxADir = Up;
									boxBDir = Down;
								}
								else
								{
									boxADir = Down;
									boxBDir = Up;
								}
							}
							else
							{
								if (diff.x > 0)
								{
									boxADir = Left;
									boxBDir = Right;
								}
								else
								{
									boxADir = Right;
									boxBDir = Left;
								}
							}
							
							(*vecItA)->onCollision(*vecItB, min(horPenetration, verPenetration), boxADir);
							(*vecItB)->onCollision(*vecItA, min(horPenetration, verPenetration), boxBDir);
						}
					}
				}
			}
		}
	}
}
