#pragma once

#include <iostream>
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>
#include "Exports.h"
#include "EngineConstants.h"

namespace gn
{
	class Renderer;
/*
	An "Entity" is used as a base class for all the sorts of enities that the game will have, from simple
	shapes to detailed sprites.
*/
	class ENGINE_API Entity
	{
	protected:
		Renderer* _renderer;

		glm::vec3 _position;
		glm::vec3 _rotation;
		glm::vec3 _scale;

		glm::mat4 _traMatrix;
		glm::mat4 _rotMatrix;
		glm::mat4 _scaMatrix;

		glm::mat4 _modelMatrix;

		void updateModelMatrix();

	public:
		Entity(Renderer* renderer);
		Entity(Renderer* renderer, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
		virtual ~Entity();

		virtual void translate(float x, float y, float z);
		virtual void rotate(float x, float y, float z);
		virtual void scale(float x, float y, float z);

		virtual void setPosition(float x, float y, float z);
		virtual void setRotation(float x, float y, float z);
		virtual void setScale(float x, float y, float z);

		inline glm::vec3 getPosition() const { return _position; }
		inline glm::vec3 getRotation() const { return _rotation; }
		inline glm::vec3 getScale() const { return _scale; }
	};
}