#pragma once

#include "Shape.h"

namespace gn
{
	/*
		A "Shape" that represents a tridimensional object; it is composed of 36 vertices (6 vertices for each of the
		6 faces of the cube).
	*/
	class ENGINE_API Cube : public Shape
	{
	public:
		Cube(Renderer* renderer, Material* material);
		~Cube();

		float* setVertices(unsigned int vertexComponents, float width = 1.0f, float height = 1.0f, float depth = 1.0f) const override;

		void draw() const override;
	};
}
