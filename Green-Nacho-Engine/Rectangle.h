#pragma once

#include "Shape.h"

namespace gn
{
	namespace legacy
	{
/*
	A "Shape" that represents a quad; it always has four vertices, and it supports individually
	colored vertices through the use of a vertex shader.
*/
		class ENGINE_DECL_SPEC Rectangle : public Shape
		{
		private:
			float _width;
			float _height;

		protected:
			float* generateVertexBufferData() const override;

		public:
			Rectangle(Renderer* renderer, Material* material, float width = 1.0f, float height = 1.0f, float *colorBufferData = NULL);
			~Rectangle();

			void draw() const override;
		};
	}
}