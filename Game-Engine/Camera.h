#pragma once

#include "Entity.h"
#include "Exports.h"
#include "EngineConstants.h"

namespace gn
{
	class Renderer;

	class ENGINE_API Camera : Entity
	{
	private:
		glm::vec3 _up;
		glm::vec3 _forward;
		glm::vec3 _right;

		void updateRenderer();

	public:	
		Camera(Renderer* renderer, glm::vec3 position, glm::vec3 rotation, 
		glm::vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f));

		void advance(const float distance);
		void strafe(const float distance);
		void ascend(const float distance);
		
		void pitch(const float angle);
		void yaw(const float angle);
		void roll(const float angle);
	};
}