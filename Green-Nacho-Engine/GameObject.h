#pragma once

#include <iostream>
#include <algorithm>
#include <list>
#include <glm/mat4x4.hpp>
#include "Exports.h"
#include "Enums.h"

namespace gn
{
	class Renderer;
	class Component;
	class Transform;

	class ENGINE_API GameObject
	{
	private:
		Renderer* _renderer;
		Transform* _transform;
		std::list<Component*>* _components;
		std::list<GameObject*>* _children;

	public:
		GameObject(Renderer* renderer, GameObject* parent = NULL);
		~GameObject();

		void start();
		void stop();

		void update();
		void draw();

		bool addChild(GameObject* gameObject);
		bool removeChild(GameObject* gameObject);

		Component* addComponent(ComponentID componentID);
		bool removeComponent(ComponentID componentID);

		Component* getComponent(ComponentID componentID);

		inline Transform* getTransform() { return _transform; }
	};
}