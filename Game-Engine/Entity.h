#pragma once

#include <iostream>
#include "Exports.h"
#include <glm.hpp>
using namespace std;
using namespace glm;

class Renderer;

class ENGINE_API Entity
{
protected:
	Renderer* _renderer;

	vec3 _position;
	vec3 _rotation;
	vec3 _scale;

	mat4 _translation;
	mat4 _rotationX;
	mat4 _rotationY;
	mat4 _rotationZ;
	mat4 _scaling;

	mat4 _model;

	void updateModelMatrix();

public:
	Entity(Renderer* renderer);
	virtual ~Entity();

	virtual void draw() const = 0;

	void setPosition(float x, float y, float z);
	void setRotation(float x, float y, float z);
	void setScale(float x, float y, float z);

	vec3 getPosition() { return _position; }
	vec3 getRotation() { return _rotation; }
	vec3 getScale() { return _scale; }
};