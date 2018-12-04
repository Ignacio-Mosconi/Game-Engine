#pragma once

#include "Shape.h"
#include "Exports.h"

namespace gn
{
/*
	A "Shape" that represents a triangle; it is a really simple "Entity", with only three verices.
*/
	class ENGINE_API Triangle : public Shape
	{
	public:
		Triangle(Renderer* renderer, Material* material);
		~Triangle();

		float* setVertices(unsigned int vertexComponents, float width = 1.0f, float height = 1.0f) const override;

		void draw() const override;
	};
}