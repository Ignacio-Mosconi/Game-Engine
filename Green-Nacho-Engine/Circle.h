#pragma once

#include <glm\gtc\constants.hpp>
#include "Shape.h"

namespace gn
{
/*
	A "Shape" that represents a circle; it may have multiple vertices to define its
	circumference.
*/
	class ENGINE_DECL_SPEC Circle : public Shape
	{
	private:
		unsigned int _vertexCount;
		float _radius;

	protected:
		float* generateVertexBufferData() const override;

	public:
		Circle(Renderer* renderer, Material* material, unsigned int vertexCount = 20.0f, float radius = 1.0f, float* colorBufferData = NULL);
		~Circle();

		void draw() const override;
	};
}