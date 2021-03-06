#pragma once
#pragma warning(disable: 4251)

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Core/Exports.h"
#include "Core/EngineConstants.h"
#include "Scene Graph/Component.h"

namespace gn
{
	class ENGINE_DECL_SPEC Transform : public Component
	{
	private:
		glm::vec3 _position;
		glm::vec3 _rotation;
		glm::vec3 _scale;		
		
		glm::vec3 _forward;
		glm::vec3 _right;
		glm::vec3 _up;		
		
		glm::vec3 _localForward;
		glm::vec3 _localRight;
		glm::vec3 _localUp;

		glm::mat4 _traMatrix;
		glm::mat4 _rotMatrix;
		glm::mat4 _scaMatrix;

		glm::mat4 _modelMatrix;

		void updateModelMatrix();
		void updateRotationMatrix();
		void updateDirectionVectors();
		void clampEulerRotation();

	public:
		Transform(GameObject* gameObject);
		Transform(GameObject* gameObject, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
		virtual ~Transform();

		void translate(float x, float y, float z);
		void rotate(float x, float y, float z);
		void scale(float x, float y, float z);

		void setPosition(float x, float y, float z);
		void setRotation(float x, float y, float z);
		void setScale(float x, float y, float z);

		glm::vec3 getGlobalPosition() const;
		glm::vec3 getGlobalRotation() const;

		void setGlobalPosition(float x, float y, float z);
		void setGlobalRotation(float x, float y, float z);

		void forceLocalUp();
		void forceLocalForward(glm::vec3 newForward);
		void changeRotationMatrix(glm::vec4 quaternion);

		static void convertToEulerAngles(const glm::vec4& quaternion, float& pitch, float& yaw, float& roll);
		static glm::vec4 convertToQuaternion(float pitch, float yaw, float roll);

		inline glm::vec3 getPosition() const { return _position; }
		inline glm::vec3 getRotation() const { return _rotation; }
		inline glm::vec3 getScale() const { return _scale; }
		
		inline glm::vec3 getForward() const { return _forward; }
		inline glm::vec3 getRight() const { return _right; }
		inline glm::vec3 getUp() const { return _up; }		
		
		inline glm::vec3 getLocalForward() const { return _localForward; }
		inline glm::vec3 getLocalRight() const { return _localRight; }
		inline glm::vec3 getLocalUp() const { return _localUp; }

		inline glm::mat4 getRotMatrix() const { return _rotMatrix; }

		inline glm::mat4 getModelMatrix() const { return _modelMatrix; }
	};
}