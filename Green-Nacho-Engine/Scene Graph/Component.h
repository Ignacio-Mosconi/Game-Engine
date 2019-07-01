#pragma once

#include <string>
#include "Core/Exports.h"

namespace gn
{
	enum class ComponentID
	{
		Transform,
		SpriteRenderer,
		MeshRenderer,
		CapsuleCollider,
		RigidBody
	};

	class ENGINE_DECL_SPEC Component
	{
	private:
		ComponentID _id;

	public:
		virtual void start();
		virtual void stop();
		virtual void update();
		virtual void draw() const;

		Component(ComponentID id);
		~Component();

		static Component* generateComponent(ComponentID componentID);

		inline ComponentID getID() const { return _id; }
	};
}