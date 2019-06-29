#pragma once

#include <iostream>
#include <algorithm>
#include <list>
#include <glm/mat4x4.hpp>
#include "Exports.h"

namespace gn
{
	enum class ComponentID;
	class Renderer;
	class Component;
	class Transform;

	class ENGINE_DECL_SPEC GameObject
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
		GameObject* getChild(unsigned int childIndex);

		Component* addComponent(ComponentID componentID);
		bool removeComponent(ComponentID componentID);
		Component* getComponent(ComponentID componentID);

		inline Renderer* getRenderer() { return _renderer; }
		inline Transform* getTransform() { return _transform; }
	};
}