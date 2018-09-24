#include "Entity.h"
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtx\transform.hpp>

Entity::Entity(Renderer* renderer) : _renderer(renderer),
_position(vec3(0, 0, 0)), _rotation(vec3(0, 0, 0)), _scale(vec3(1, 1, 1)),
_traMatrix(mat4(1.0f)), _rotMatrix(mat4(1.0f)), _scaMatrix(mat4(1.0f))
{
	cout << "Entity::Entity()" << endl;
}

Entity::~Entity()
{
	cout << "Entity::~Entity()" << endl;
}

void Entity::updateModelMatrix()
{
	cout << "Entity::updateModelMatrix()" << endl;

	_modelMatrix = _traMatrix * _rotMatrix * _scaMatrix;
}

void Entity::setPosition(float x, float y, float z)
{
	cout << "Entity::setPosition(x, y, z)" << endl;

	_position = vec3(x, y, z);
	
	_traMatrix = translate(mat4(1.0f), _position);

	updateModelMatrix();
}

void Entity::setRotation(float x, float y, float z)
{
	cout << "Entity::setRotation(x, y, z)" << endl;

	_rotation = vec3(x, y, z);

	mat4 rotationX = rotate(mat4(1.0f), x, vec3(1, 0, 0));
	mat4 rotationY = rotate(mat4(1.0f), y, vec3(0, 1, 0));
	mat4 rotationZ = rotate(mat4(1.0f), z, vec3(0, 0, 1));

	_rotMatrix = rotationX * rotationY * rotationZ;

	updateModelMatrix();
}

void Entity::setScale(float x, float y, float z)
{
	cout << "Entity::setScale(x, y, z)" << endl;

	_scale = vec3(x, y, z);

	_scaMatrix = scale(mat4(1.0f), _scale);

	updateModelMatrix();
}