#pragma once

#include <map>
#include <vector>
#include <glm.hpp>
#include "Exports.h"

using namespace std;
using namespace glm;

class BoundingBox;

class ENGINE_API CollisionManager
{
private:
	static CollisionManager* _instance;

	map<string, vector<BoundingBox*>> _collisionLayers;

	CollisionManager();
	~CollisionManager();

public:
	static CollisionManager* getInstance();
	static void deleteInstance();

	void registerBoundingBox(BoundingBox* box, string& layer);
	bool deregisterBoundingBox(BoundingBox* box);

	void update();
};

