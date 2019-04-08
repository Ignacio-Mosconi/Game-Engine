#include "Entity.h"
#include "Renderer.h"

namespace gn
{
	Entity::Entity(Renderer* renderer) :
	_renderer(renderer),
	_position(glm::vec3(0, 0, 0)), _rotation(glm::vec3(0, 0, 0)), _scale(glm::vec3(1, 1, 1)),
	_traMatrix(glm::mat4(1.0f)), _rotMatrix(glm::mat4(1.0f)), _scaMatrix(glm::mat4(1.0f)), _modelMatrix(glm::mat4(1.0f))
	{
		std::cout << "Entity::Entity()" << std::endl;
	}

	Entity::~Entity()
	{
		std::cout << "Entity::~Entity()" << std::endl;
	}

	void Entity::updateModelMatrix()
	{
		_modelMatrix = _traMatrix * _rotMatrix * _scaMatrix;
	}

	void Entity::setPosition(float x, float y, float z)
	{
		_position = glm::vec3(x, y, z);
	
		_traMatrix = glm::translate(glm::mat4(1.0f), _position);

		updateModelMatrix();
	}

	void Entity::setRotation(float x, float y, float z)
	{
		_rotation = glm::vec3(x, y, z);

		glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), x, glm::vec3(1, 0, 0));
		glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), y, glm::vec3(0, 1, 0));
		glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), z, glm::vec3(0, 0, 1));

		_rotMatrix = rotationX * rotationY * rotationZ;

		updateModelMatrix();
	}

	void Entity::setScale(float x, float y, float z)
	{
		_scale = glm::vec3(x, y, z);

		_scaMatrix = glm::scale(glm::mat4(1.0f), _scale);

		updateModelMatrix();
	}

	void Entity::translate(float x, float y, float z)
	{
		_position += glm::vec3(x, y, z);

		_traMatrix = glm::translate(glm::mat4(1.0f), _position);

		updateModelMatrix();
	}

	void Entity::rotate(float x, float y, float z)
	{
		_rotation += glm::vec3(x, y, z);

		if (_rotation.x < 0 || _rotation.x > FULL_ROTATION)
			_rotation.x = glm::abs(FULL_ROTATION - glm::abs(_rotation.x));		
		if (_rotation.y < 0 || _rotation.y > FULL_ROTATION)
			_rotation.y = glm::abs(FULL_ROTATION - glm::abs(_rotation.y));		
		if (_rotation.z < 0 || _rotation.z > FULL_ROTATION)
			_rotation.z = glm::abs(FULL_ROTATION - glm::abs(_rotation.z));

		glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), _rotation.x, glm::vec3(1, 0, 0));
		glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), _rotation.y, glm::vec3(0, 1, 0));
		glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), _rotation.z, glm::vec3(0, 0, 1));

		_rotMatrix = rotationX * rotationY * rotationZ;

		updateModelMatrix();
	}

	void Entity::scale(float x, float y, float z)
	{
		_scale += glm::vec3(x, y, z);

		_scaMatrix = glm::scale(glm::mat4(1.0f), _scale);

		updateModelMatrix();
	}
}