#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "Exports.h"
#include "EngineConstants.h"
#include "Component.h"

namespace gn
{
	class Renderer;

	class ENGINE_API Transform : public Component
	{
	private:
		glm::vec3 _position;
		glm::vec3 _rotation;
		glm::vec3 _scale;

		glm::mat4 _traMatrix;
		glm::mat4 _rotMatrix;
		glm::mat4 _scaMatrix;

		glm::mat4 _modelMatrix;

		void updateModelMatrix();
		void clampEulerRotation();

	public:
		Transform();
		Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
		virtual ~Transform();

		void translate(float x, float y, float z);
		void rotate(float x, float y, float z);
		void scale(float x, float y, float z);

		void setPosition(float x, float y, float z);
		void setRotation(float x, float y, float z);
		void setScale(float x, float y, float z);

		inline glm::vec3 getPosition() const { return _position; }
		inline glm::vec3 getRotation() const { return _rotation; }
		inline glm::vec3 getScale() const { return _scale; }

		inline glm::mat4 getModelMatrix() const { return _modelMatrix; }
	};
}