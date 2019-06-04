#pragma once

#include <string>
#include <glm/mat4x4.hpp>
#include "Exports.h"

namespace gn
{
	class ENGINE_API Component
	{
	private:
		std::string _id;

	public:
		virtual void start() = 0;
		virtual void stop() = 0;
		virtual void update() = 0;
		virtual void draw(glm::mat4 modelMatrix) const = 0;

		Component(const std::string& id);
		~Component();

		inline std::string getID() const { return _id; }
	};
}