#pragma once

#include <string>
#include "Core/Exports.h"

namespace gn
{
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
	private:
		ComponentID _id;

	public:
		virtual void start();
		virtual void stop();
		virtual void update(float deltaTime);
		virtual void draw() const;

		Component(ComponentID id);
		~Component();

		static Component* generateComponent(ComponentID componentID);

		inline ComponentID getID() const { return _id; }
	};
}