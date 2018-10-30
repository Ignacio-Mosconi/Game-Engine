#pragma once

#include <map>
#include <vector>
#include <glm.hpp>
#include "Exports.h"

using namespace std;
using namespace glm;

class Avatar;

class ENGINE_API CollisionManager
{
private:
	static CollisionManager* _instance;

	map<string, vector<Avatar*>> _collisionLayers;

	CollisionManager();
	~CollisionManager();

public:
	static CollisionManager* getInstance();
	static void deleteInstance();

	void registerAvatar(Avatar* avatar, string layer);

	void update();
};

