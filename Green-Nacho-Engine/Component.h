#pragma once

#include <string>
#include "Exports.h"
#include "Enums.h"

namespace gn
{
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