#include "Transform.h"
#include "Renderer.h"

namespace gn
{
	Transform::Transform() : Component(ComponentID::Transform),
		_position(glm::vec3(0.0f, 0.0f, 0.0f)), _rotation(glm::vec3(0.0f, 0.0f, 0.0f)), _scale(glm::vec3(1.0f, 1.0f, 1.0f)),
		_traMatrix(glm::mat4(1.0f)), _rotMatrix(glm::mat4(1.0f)), _scaMatrix(glm::mat4(1.0f))
	{
		updateModelMatrix();
	}

	Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : Component(ComponentID::Transform),
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
	
	void Transform::clampEulerRotation()
	{
		if (_rotation.x < 0 || _rotation.x > FULL_ROTATION)
			_rotation.x = glm::abs(FULL_ROTATION - glm::abs(_rotation.x));
		if (_rotation.y < 0 || _rotation.y > FULL_ROTATION)
			_rotation.y = glm::abs(FULL_ROTATION - glm::abs(_rotation.y));
		if (_rotation.z < 0 || _rotation.z > FULL_ROTATION)
			_rotation.z = glm::abs(FULL_ROTATION - glm::abs(_rotation.z));
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

		glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), _rotation.x, glm::vec3(1, 0, 0));
		glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), _rotation.y, glm::vec3(0, 1, 0));
		glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), _rotation.z, glm::vec3(0, 0, 1));

		_rotMatrix = rotationX * rotationY * rotationZ;

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

		glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), x, glm::vec3(1, 0, 0));
		glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), y, glm::vec3(0, 1, 0));
		glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), z, glm::vec3(0, 0, 1));

		_rotMatrix = rotationX * rotationY * rotationZ;

		updateModelMatrix();
	}

	void Transform::setScale(float x, float y, float z)
	{
		_scale= glm::vec3(x, y, z);
		_scaMatrix = glm::scale(glm::mat4(1.0f), _scale);

		updateModelMatrix();
	}
}