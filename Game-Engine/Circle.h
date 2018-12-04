#pragma once

#include <glm\gtc\constants.hpp>
#include "Shape.h"
#include "Exports.h"

namespace gn
{
/*
	A "Shape" that represents a circle; it may have multiple vertices to define its
	circumference.
*/
	class ENGINE_API Circle : public Shape
	{
	public:
		Circle(Renderer* renderer, Material* material, unsigned int vertexCount);
		~Circle();

		float* setVertices(unsigned int vertexComponents, float width = 1.0f, float height = 1.0f) const override;

		void draw() const override;
	};
}