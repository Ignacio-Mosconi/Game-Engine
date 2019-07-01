#include "Scene Graph/GameObject.h"
#include "Core/Renderer.h"
#include "Scene Graph/Component.h"
#include "Scene Graph/Transform.h"

namespace gn
{
	GameObject::GameObject(Renderer* renderer, GameObject* parent):
		_renderer(renderer), _transform(new Transform()),
		_components(new std::list<Component*>()), _children(new std::list<GameObject*>())
	{
		if (parent)
			parent->addChild(this);
	}

	GameObject::~GameObject()
	{
		delete _transform;
		delete _components;
		delete _children;
	}

	void GameObject::start()
	{
		for (std::list<Component*>::iterator it = _components->begin(); it != _components->end(); it++)
			(*it)->start();
		for (std::list<GameObject*>::iterator it = _children->begin(); it != _children->end(); it++)
			(*it)->start();
	}

	void GameObject::stop()
	{
		for (std::list<Component*>::iterator it = _components->begin(); it != _components->end(); it++)
		{
			(*it)->stop();
			delete *it;
		}
		for (std::list<GameObject*>::iterator it = _children->begin(); it != _children->end(); it++)
		{
			(*it)->stop();
			delete *it;
		}
	}

	void GameObject::update(float deltaTime)
	{
		for (std::list<Component*>::iterator it = _components->begin(); it != _components->end(); it++)
			(*it)->update(deltaTime);
		for (std::list<GameObject*>::iterator it = _children->begin(); it != _children->end(); it++)
			(*it)->update(deltaTime);
	}

	void GameObject::draw()
	{
		glm::mat4 originalModelMatrix = _renderer->getModelMatrix();
		glm::mat4 originalViewMatrix = _renderer->getViewMatrix();
		glm::mat4 originalProjectionMatrix = _renderer->getProjectionMatrix();
		
		_renderer->multiplyModelMatrix(_transform->getModelMatrix());

		for (std::list<Component*>::iterator it = _components->begin(); it != _components->end(); it++)
			(*it)->draw();
		for (std::list<GameObject*>::iterator it = _children->begin(); it != _children->end(); it++)
			(*it)->draw();

		_renderer->setModelMatrix(originalModelMatrix);
		_renderer->setViewMatrix(originalViewMatrix);
		_renderer->setProjectionMatrix(originalProjectionMatrix);
	}

	bool GameObject::addChild(GameObject* gameObject)
	{
		bool added = false;

		std::list<GameObject*>::iterator it = std::find(_children->begin(), _children->end(), gameObject);

		if (it == _children->end())
		{
			_children->push_back(gameObject);
			added = true;
		}

		return added;
	}

	bool GameObject::removeChild(GameObject* gameObject)
	{
		bool removed = false;

		std::list<GameObject*>::iterator it = std::find(_children->begin(), _children->end(), gameObject);

		if (it != _children->end())
		{
			_children->remove(gameObject);
			removed = true;
		}

		return removed;
	}

	GameObject* GameObject::getChild(unsigned int childIndex)
	{
		GameObject* child = NULL;

		if (childIndex < _children->size())
			child = *(std::next(_children->begin(), childIndex));

		return child;
	}

	Component* GameObject::addComponent(ComponentID componentID)
	{
		Component* component = NULL;

		std::list<Component*>::iterator it = std::find_if(_components->begin(), _components->end(),
			[&componentID](const Component* comp) {return comp->getID() == componentID; });
		
		if (it == _components->end())
		{
			component = Component::generateComponent(componentID);
			_components->push_back(component);
		}

		return component;
	}

	bool GameObject::removeComponent(ComponentID componentID)
	{
		bool removed = false;
		std::list<Component*>::iterator it = std::find_if(_components->begin(), _components->end(),
			[&componentID](const Component* comp) {return comp->getID() == componentID; });

		if (it != _components->end())
		{
			_components->remove(*it);
			delete *it;
			removed = true;
		}

		return removed;
	}

	Component* GameObject::getComponent(ComponentID componentID)
	{
		Component* component = NULL;
		std::list<Component*>::iterator it = std::find_if(_components->begin(), _components->end(),
			[&componentID](const Component* comp) {return comp->getID() == componentID; });

		if (it != _components->end())
			component = *it;

		return component;
	}
}