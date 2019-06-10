#pragma once

#include <string>
#include "Exports.h"

namespace gn
{
	class ENGINE_API Component
	{
	private:
		std::string _id;

	public:
		virtual void start() {}
		virtual void stop() {}
		virtual void update() {}
		virtual void draw() const {}

		Component(const std::string& id) {}
		~Component() {}

		inline std::string getID() const { return _id; }
	};
}