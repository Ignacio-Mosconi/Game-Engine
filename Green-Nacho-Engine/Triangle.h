#pragma once

#include "Shape.h"

namespace gn
{
/*
	A "Shape" that represents a triangle; it is a really simple "Entity", with only three verices.
*/
	class ENGINE_API Triangle : public Shape
	{
	private:
		float _base;
		float _height;

	protected:
		float* generateVertexBufferData() const override;

	public:
		Triangle(Renderer* renderer, Material* material, float base = 1.0f, float height = 1.0f, float* colorBufferData = NULL);
		~Triangle();

		void draw() const override;
	};
}