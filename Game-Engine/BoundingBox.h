#pragma once

#include <iostream>
#include <glm.hpp>
#include "Exports.h"
#include "Entity.h"

using namespace std;
using namespace glm;

enum CollisionDir
{
	Left, Right, Up, Down
};

class GameEntity;

/*
The "BoundingBox" is a box collider that is used as a way of detecting collisions between entities;
each of these must be attached to an "Entity", as well as be registered inside the "CollisionManager" class.
*/

class ENGINE_API BoundingBox
{
private:
	Entity* _entityAttached;
	GameEntity* _gameEntityAttached;
	bool _staticObject;
	float _width;
	float _height;
	float _mass;

public:
	BoundingBox(float width, float height, bool staticObject = false, float mass = 1);
	~BoundingBox();

	void attachToEntity(Entity* entity);
	void attachToGameEntity(GameEntity* entity);
	void onCollision(BoundingBox* collider, float penetration, CollisionDir direction);
	void setPhysicalProperties(bool staticObject, float mass);

	void setWidth(float width) { _width = width; }
	void setHeight(float height) { _height = _height; }
	
	inline vec3 getEntityAttachedPosition() const { return _entityAttached->getPosition(); }
	inline float getWidth() const { return _width; }
	inline float getHeight() const { return _height; }
	inline bool isStatic() const { return _staticObject; }
	inline float getMass() const { return _mass; }
};
