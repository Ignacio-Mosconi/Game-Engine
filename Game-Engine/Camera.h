#pragma once

#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>
#include "Exports.h"
#include "EngineConstants.h"

namespace gn
{
	class Renderer;

	class ENGINE_API Camera
	{
	private:
		Renderer* _renderer;

		glm::vec3 _position;
		glm::vec3 _rotation;
		
		glm::vec3 _up;
		glm::vec3 _forward;
		glm::vec3 _right;

		void updateRenderer();

	public:
		Camera(Renderer* renderer);
		Camera(Renderer* renderer, glm::vec3 pos, glm::vec3 rot = glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f));

		void advance(const float distance);
		void strafe(const float distance);
		void ascend(const float distance);
		
		void pitch(const float angle);
		void yaw(const float angle);
		void roll(const float angle);
	};
}