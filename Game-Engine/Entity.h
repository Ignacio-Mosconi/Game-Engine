#pragma once

#include <iostream>
#include <glm.hpp>
#include "Exports.h"
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

	mat4 _traMatrix;
	mat4 _rotMatrix;
	mat4 _scaMatrix;

	mat4 _modelMatrix;

	void updateModelMatrix();

public:
	Entity(Renderer* renderer);
	virtual ~Entity();

	virtual void draw() const = 0;

	void setPosition(float x, float y, float z);
	void setRotation(float x, float y, float z);
	void setScale(float x, float y, float z);

	void translate(float x, float y, float z);
	void rotate(float x, float y, float z);
	void scale(float x, float y, float z);

	inline vec3 getPosition() const { return _position; }
	inline vec3 getRotation() const { return _rotation; }
	inline vec3 getScale() const { return _scale; }
};