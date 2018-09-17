#include "Entity.h"
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtx\transform.hpp>

Entity::Entity(Renderer* renderer) : _renderer(renderer),
_position(vec3(0, 0, 0)), _rotation(vec3(0, 0, 0)), _scale(vec3(1, 1, 1)),
_translation(mat4(1.0f)), _rotationX(mat4(1.0f)), _rotationY(mat4(1.0f)), _rotationZ(mat4(1.0f)), _scaling(mat4(1.0f))
{
	cout << "Entity::Entity()" << endl;
}

Entity::~Entity()
{
	cout << "Entity::~Entity()" << endl;
}

void Entity::updateModelMatrix()
{
	cout << "Entity::~updateModelMatrix()" << endl;

	_model = _translation * _rotationX * _rotationY * _rotationZ * _scaling;
}

void Entity::setPosition(float x, float y, float z)
{
	cout << "Entity::~setPosition(x, y, z)" << endl;

	_position = vec3(x, y, z);
	
	_translation = translate(mat4(1.0f), _position);

	updateModelMatrix();
}

void Entity::setRotation(float x, float y, float z)
{
	cout << "Entity::~setRotation(x, y, z)" << endl;

	_rotation = vec3(x, y, z);

	_rotationX = rotate(mat4(1.0f), x, vec3(1, 0, 0));
	_rotationY = rotate(mat4(1.0f), y, vec3(0, 1, 0));
	_rotationZ = rotate(mat4(1.0f), z, vec3(0, 0, 1));

	updateModelMatrix();
}

void Entity::setScale(float x, float y, float z)
{
	cout << "Entity::~setScale(x, y, z)" << endl;

	_scale = vec3(x, y, z);

	_scaling = scale(mat4(1.0f), _scale);

	updateModelMatrix();
}