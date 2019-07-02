#pragma once

#include <string>
#include "Core/Exports.h"

namespace gn
{
	class GameObject;

	enum class ComponentID
	{
		Transform,
		Camera,
		SpriteRenderer,
		MeshRenderer,
		CapsuleCollider,
		RigidBody,
		NavigationController
	};

	class ENGINE_DECL_SPEC Component
	{
	protected:
		ComponentID _id;
		GameObject* _gameObject;

	public:
		virtual void start();
		virtual void stop();
		virtual void update(float deltaTime);
		virtual void draw() const;

		Component(ComponentID id, GameObject* gameObject);
		~Component();

		static Component* generateComponent(ComponentID componentID, GameObject* gameObject);

		inline ComponentID getID() const { return _id; }
		inline GameObject* getGameObject() const { return _gameObject; }
	};
}