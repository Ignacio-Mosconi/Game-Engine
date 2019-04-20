#include "CollisionManager.h"
#include "Entity.h"
#include "BoundingBox.h"

namespace gn
{
	CollisionManager* CollisionManager::_instance = NULL;

	CollisionManager::CollisionManager()
	{
		std::cout << "CollisionManager::CollisionManager()" << std::endl;
	}

	CollisionManager::~CollisionManager()
	{
		std::cout << "CollisionManager::~CollisionManager()" << std::endl;
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

	void CollisionManager::registerBoundingBox(BoundingBox* box, const std::string& layer)
	{	
		_collisionLayers[layer].push_back(box);
	}

	bool CollisionManager::deregisterBoundingBox(BoundingBox* box)
	{	
		bool wasDeregistered = false;

		std::map<std::string, std::vector<BoundingBox*>>::iterator mapIt;
		std::vector<BoundingBox*>::iterator vecIt;

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
		std::map<std::string, std::vector<BoundingBox*>>::iterator mapItA;
		std::map<std::string, std::vector<BoundingBox*>>::iterator mapItB;
		std::vector<BoundingBox*>::iterator vecItA;
		std::vector<BoundingBox*>::iterator vecItB;
	
		for (mapItA = _collisionLayers.begin(); mapItA != _collisionLayers.end(); mapItA++)
		{
			for (vecItA = mapItA->second.begin(); vecItA != mapItA->second.end(); vecItA++)
			{
				glm::vec2 posA((*vecItA)->getEntityAttachedPosition().x, (*vecItA)->getEntityAttachedPosition().y);
				float bbWidthA = (*vecItA)->getWidth();
				float bbHeightA = (*vecItA)->getHeight();

				for (mapItB = _collisionLayers.begin(); mapItB != _collisionLayers.end(); mapItB++)
				{
					if (mapItA->first != mapItB->first)
					{
						for (vecItB = mapItB->second.begin(); vecItB != mapItB->second.end(); vecItB++)
						{
							glm::vec2 posB((*vecItB)->getEntityAttachedPosition().x, (*vecItB)->getEntityAttachedPosition().y);
							float bbWidthB = (*vecItB)->getWidth();
							float bbHeightB = (*vecItB)->getHeight();

							float minDistX = (bbWidthA + bbWidthB) / 2;
							float minDistY = (bbHeightA + bbHeightB) / 2;

							glm::vec2 diff = posB - posA;
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
										boxADir = CollisionDir::UP;
										boxBDir = CollisionDir::DOWN;
									}
									else
									{
										boxADir = CollisionDir::DOWN;
										boxBDir = CollisionDir::UP;
									}
								}
								else
								{
									if (diff.x > 0)
									{
										boxADir = CollisionDir::LEFT;
										boxBDir = CollisionDir::RIGHT;
									}
									else
									{
										boxADir = CollisionDir::RIGHT;
										boxBDir = CollisionDir::LEFT;
									}
								}
							
								(*vecItA)->onCollision(*vecItB, glm::min(horPenetration, verPenetration), boxADir);
								(*vecItB)->onCollision(*vecItA, glm::min(horPenetration, verPenetration), boxBDir);
							}
						}
					}
				}
			}
		}
	}
}