#pragma once

#include "Exports.h"

#include <algorithm>
#include <list>

namespace gn
{
	class Component;
	class Transform;

	class ENGINE_API GameObject
	{
	private:
		Transform* _transform;
		std::list<Component*>* _components;
		std::list<GameObject*>* _children;

	public:
		GameObject();
		~GameObject();

		void start();
		void stop();

		void update();
		void draw();

		bool addChild(GameObject* gameObject);
		bool removeChild(GameObject* gameObject);

		bool addComponent(Component* component);
		bool removeComponent(const std::string& componentID);

		Component* getComponent(const std::string& componentID);
	};
}