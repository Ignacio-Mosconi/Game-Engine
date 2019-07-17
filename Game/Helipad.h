#pragma once

#include <time.h>
#include <stdlib.h>
#include <glm/vec2.hpp>
#include "Scene Graph/GameObject.h"
#include "Scene Graph/Transform.h"
#include "Scene Graph/BoundingBox.h"
#include "Scene Graph/BoxCollider.h"
#include "Scene Graph/RigidBody.h"
#include "Scene Graph/ModelLoader.h"
#include "GameConstants.h"

class Helipad
{
private:
	gn::GameObject* _platform;

	float _heightPosition;

public:
	Helipad();
	~Helipad();

	void start(gn::GameObject* scene, float heightPosition, glm::vec2 minHorPos, glm::vec2 maxHorPos);
	void setRandomPosition(glm::vec2 min, glm::vec2 max);

	inline gn::GameObject* getPlatformObject() const { return _platform; }
};
