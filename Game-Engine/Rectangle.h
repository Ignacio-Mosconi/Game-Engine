#pragma once

#include "Shape.h"

namespace gn
{
/*
	A "Shape" that represents a quad; it always has four vertices, and it supports individually
	colored vertices through the use of a vertex shader.
*/
	class ENGINE_API Rectangle : public Shape
	{
	public:
		Rectangle(Renderer* renderer, Material* material);
		~Rectangle();

		float* setVertices(unsigned int vertexComponents, float width = 1.0f, float height = 1.0f) const override;

		void draw() const override;
	};
}