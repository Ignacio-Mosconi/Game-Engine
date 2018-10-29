#pragma once

#include <map>
#include <vector>
#include <glm.hpp>
#include "Exports.h"

using namespace std;

class Entity;

class ENGINE_API CollisionManager
{
private:
	static CollisionManager* _instance;

	map<string, vector<Entity*>> collisionLayers;

	CollisionManager();
	~CollisionManager();

public:
	static CollisionManager* getInstance();
	static void deleteInstance();

	void registerEntity(Entity* entity, string collisionLayer);

	void update();
};

