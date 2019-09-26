#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <glm/mat4x4.hpp>
#include "Core/Exports.h"

namespace gn
{
	enum class ComponentID;
	class Renderer;
	class Component;
	class Transform;
	class Camera;
	class BspPlane;

	class ENGINE_DECL_SPEC GameObject
	{
	private:
		Renderer* _renderer;
		Transform* _transform;
		Transform* _parentTransform;

		std::list<Component*>* _components;
		std::list<GameObject*>* _children;

	public:
		GameObject(Renderer* renderer, GameObject* parent = NULL);
		~GameObject();

		void start();
		void stop();

		void update(float deltaTime);
		void draw(Camera* activeCamera, std::vector<BspPlane*> bspPlanes, int& objectsDrawn);

		bool addChild(GameObject* gameObject);
		bool removeChild(GameObject* gameObject);
		GameObject* getChild(unsigned int childIndex);

		Component* addComponent(ComponentID componentID);
		bool removeComponent(ComponentID componentID);
		Component* getComponent(ComponentID componentID);
		Component* getComponentInChildren(ComponentID componentID);
		std::vector<Component*> getComponentsInChildren(ComponentID componentID);

		inline unsigned int getChildCount() { return (unsigned int)_children->size(); }

		inline Renderer* getRenderer() { return _renderer; }
		inline Transform* getTransform() { return _transform; }
		inline Transform* getParentTransform() { return _parentTransform; }
	};
}