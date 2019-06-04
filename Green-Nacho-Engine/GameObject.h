#pragma once

#include <iostream>
#include <algorithm>
#include <list>
#include <glm/mat4x4.hpp>
#include "Exports.h"

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
		GameObject(bool addTransform = true);
		~GameObject();

		void start();
		void stop();

		void update();
		void draw(glm::mat4 parentMatrix);

		bool addChild(GameObject* gameObject);
		bool removeChild(GameObject* gameObject);

		bool addComponent(Component* component);
		bool removeComponent(const std::string& componentID);

		Component* getComponent(const std::string& componentID);
	};
}