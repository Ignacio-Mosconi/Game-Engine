#include "Entity.h"

Entity::Entity(Renderer* renderer) : _renderer(renderer)
{
	cout << "Entity::Entity()" << endl;
}

Entity::~Entity()
{
	cout << "Entity::~Entity()" << endl;
}

void Entity::draw() const
{
	cout << "Entity::draw()" << endl;
}