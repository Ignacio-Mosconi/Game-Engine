#pragma once

#include <string>
#include "Exports.h"

namespace gn
{
	enum class ComponentID
	{
		Transform,
		SpriteRenderer,
		MeshRenderer
	};

	class ENGINE_API Component
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