#include "Scene Graph/Transform.h"
#include "Scene Graph/GameObject.h"

namespace gn
{
	Transform::Transform(GameObject* gameObject) : Component(ComponentID::TRANSFORM, gameObject),
		_position(glm::vec3(0.0f, 0.0f, 0.0f)), _rotation(glm::vec3(0.0f, 0.0f, 0.0f)), _scale(glm::vec3(1.0f, 1.0f, 1.0f)),
		_forward(glm::vec3(0.0f, 0.0f, 1.0f)), _right(glm::vec3(1.0f, 0.0f, 0.0f)), _up(glm::vec3(0.0f, 1.0f, 0.0f)),
		_traMatrix(glm::mat4(1.0f)), _rotMatrix(glm::mat4(1.0f)), _scaMatrix(glm::mat4(1.0f))
	{
		updateModelMatrix();
	}

	Transform::Transform(GameObject* gameObject, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : 
		Component(ComponentID::TRANSFORM, gameObject),
		_position(position), _rotation(rotation), _scale(scale),
		_traMatrix(glm::mat4(1.0f)), _rotMatrix(glm::mat4(1.0f)), _scaMatrix(glm::mat4(1.0f))
	{
		updateModelMatrix();
	}

	Transform::~Transform()
	{

	}
	
	void Transform::updateModelMatrix()
	{
		_modelMatrix = _traMatrix * _rotMatrix * _scaMatrix;
	}

	void Transform::updateRotationMatrix()
	{
		glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		_rotMatrix = rotationX * rotationY * rotationZ;
	}

	void Transform::updateDirectionVectors()
	{
		glm::vec4 forward(0.0f, 0.0f, 1.0f, 0.0f);
		glm::vec4 right(-1.0f, 0.0f, 0.0f, 0.0f);
		glm::vec4 up(0.0f, 1.0f, 0.0f, 0.0f);

		glm::mat4 inverseRot = glm::mat4(1.0f) / _rotMatrix;

		_forward = glm::normalize((glm::vec3)(forward * inverseRot));
		_right = glm::normalize((glm::vec3)(right * inverseRot));
		_up = glm::normalize((glm::vec3)(up * inverseRot));
	}
	
	void Transform::clampEulerRotation()
	{
		if (_rotation.x < 0.0f || _rotation.x >= FULL_ROTATION)
			_rotation.x = _rotation.x - (glm::floor(_rotation.x / FULL_ROTATION) * FULL_ROTATION);
		
		if (_rotation.y < 0.0f || _rotation.y >= FULL_ROTATION)
			_rotation.y = _rotation.y - (glm::floor(_rotation.y / FULL_ROTATION) * FULL_ROTATION);
		
		if (_rotation.z < 0.0f || _rotation.z >= FULL_ROTATION)
			_rotation.z = _rotation.z - (glm::floor(_rotation.z / FULL_ROTATION) * FULL_ROTATION);
	}

	void Transform::start()
	{
		//clampEulerRotation();
		//updateRotationMatrix();
		//updateDirectionVectors();
		//updateModelMatrix();
	}

	void Transform::translate(float x, float y, float z)
	{
		_position += glm::vec3(x, y, z);
		_traMatrix = glm::translate(glm::mat4(1.0f), _position);

		updateModelMatrix();
	}

	void Transform::rotate(float x, float y, float z)
	{
		_rotation += glm::vec3(x, y, z);

		clampEulerRotation();
		updateRotationMatrix();
		updateDirectionVectors();

		updateModelMatrix();
	}

	void Transform::scale(float x, float y, float z)
	{
		_scale += glm::vec3(x, y, z);
		_scaMatrix = glm::scale(glm::mat4(1.0f), _scale);

		updateModelMatrix();
	}

	void Transform::setPosition(float x, float y, float z)
	{
		_position = glm::vec3(x, y, z);
		_traMatrix = glm::translate(glm::mat4(1.0f), _position);

		updateModelMatrix();
	}

	void Transform::setRotation(float x, float y, float z)
	{
		_rotation = glm::vec3(x, y, z);

		clampEulerRotation();	
		updateRotationMatrix();
		updateDirectionVectors();

		updateModelMatrix();
	}

	void Transform::setScale(float x, float y, float z)
	{
		_scale = glm::vec3(x, y, z);
		_scaMatrix = glm::scale(glm::mat4(1.0f), _scale);

		updateModelMatrix();
	}

	void Transform::setUp(glm::vec3 up)
	{
		_up = up;
	}

	void Transform::convertToEulerAngles(const glm::vec4& quaternion, float& pitch, float& yaw, float& roll)
	{
		float sinPitchCosYaw = 2.0f * (quaternion.w * quaternion.x + quaternion.y * quaternion.z);
		float cosPitchCosYaw = 1.0f - 2.0f * (quaternion.x * quaternion.x + quaternion.y * quaternion.y);
		pitch = glm::atan(sinPitchCosYaw, cosPitchCosYaw);

		float sinYaw = 2.0f * (quaternion.w * quaternion.y - quaternion.z * quaternion.x);
		yaw = (glm::abs(sinYaw) >= 1.0f) ? glm::sign(sinYaw) * glm::half_pi<float>() : glm::asin(sinYaw);

		float sinRollCosYaw = 2.0f * (quaternion.w * quaternion.z + quaternion.x * quaternion.y);
		float cosRollCosYaw = 1.0f - 2.0f * (quaternion.y * quaternion.y + quaternion.z * quaternion.z);
		roll = glm::atan(sinRollCosYaw, cosRollCosYaw);

		pitch = glm::degrees(pitch);
		yaw = glm::degrees(yaw);
		roll = glm::degrees(roll);
	}

	glm::vec4 Transform::convertToQuaternion(float pitch, float yaw, float roll)
	{
		glm::vec4 rotQuat;

		float cosPitch = (float)cos(glm::radians(pitch) * 0.5);
		float sinPitch = (float)sin(glm::radians(pitch) * 0.5);
		float cosYaw = (float)cos(glm::radians(yaw) * 0.5);
		float sinYaw = (float)sin(glm::radians(yaw) * 0.5);
		float cosRoll = (float)cos(glm::radians(roll) * 0.5);
		float sinRoll = (float)sin(glm::radians(roll) * 0.5);

		rotQuat.w = cosRoll * cosYaw * cosPitch + sinRoll * sinYaw * sinPitch;
		rotQuat.x = cosRoll * cosYaw * sinPitch - sinRoll * sinYaw * cosPitch;
		rotQuat.y = sinRoll * cosYaw * sinPitch + cosRoll * sinYaw * cosPitch;
		rotQuat.z = sinRoll * cosYaw * cosPitch - cosRoll * sinYaw * sinPitch;

		return rotQuat;
	}
}