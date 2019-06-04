#include "GameObject.h"
#include "Component.h"
#include "Transform.h"

namespace gn
{
	GameObject::GameObject(bool addTransform) :
		_transform(NULL),
		_components(new std::list<Component*>()), _children(new std::list<GameObject*>())
	{
		if (addTransform)
			_transform = new Transform();
	}

	GameObject::~GameObject()
	{
		if (_transform)
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
			(*it)->stop();
		for (std::list<GameObject*>::iterator it = _children->begin(); it != _children->end(); it++)
			removeChild(*it);
	}

	void GameObject::update()
	{
		for (std::list<Component*>::iterator it = _components->begin(); it != _components->end(); it++)
			(*it)->update();
		for (std::list<GameObject*>::iterator it = _children->begin(); it != _children->end(); it++)
			(*it)->update();
	}

	void GameObject::draw(glm::mat4 parentMatrix)
	{
		glm::mat4 modelMatrix = glm::mat4(1.0f);

		if (_transform)
		{
			modelMatrix = _transform->getModelMatrix();
			parentMatrix *= modelMatrix;
		}

		for (std::list<Component*>::iterator it = _components->begin(); it != _components->end(); it++)
			(*it)->draw(modelMatrix);
		for (std::list<GameObject*>::iterator it = _children->begin(); it != _children->end(); it++)
			(*it)->draw(parentMatrix);
	}

	bool GameObject::addChild(GameObject* gameObject)
	{
		bool added = false;

		std::list<GameObject*>::iterator it = std::find(_children->begin(), _children->end(), gameObject);

		if (it != _children->end())
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

	bool GameObject::addComponent(Component* component)
	{
		bool added = false;
		std::string componentID = component->getID();

		std::list<Component*>::iterator it = std::find_if(_components->begin(), _components->end(),
			[&componentID](const Component* comp) {return comp->getID() == componentID; });
		
		if (it != _components->end())
		{
			_components->push_back(component);
			added = true;
		}

		return added;
	}

	bool GameObject::removeComponent(const std::string& componentID)
	{
		bool removed = false;
		std::list<Component*>::iterator it = std::find_if(_components->begin(), _components->end(),
			[&componentID](const Component* comp) {return comp->getID() == componentID; });

		if (it != _components->end())
		{
			_components->remove(*it);
			removed = true;
		}

		return removed;
	}

	Component* GameObject::getComponent(const std::string& componentID)
	{
		Component* component = NULL;
		std::list<Component*>::iterator it = std::find_if(_components->begin(), _components->end(),
			[&componentID](const Component* comp) {return comp->getID() == componentID; });

		if (it != _components->end())
			component = *it;

		return component;
	}
}