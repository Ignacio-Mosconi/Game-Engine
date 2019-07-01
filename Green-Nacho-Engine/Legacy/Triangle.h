#pragma once

#include "Legacy/Shape.h"

namespace gn
{
	namespace legacy
	{
/*
		A "Shape" that represents a triangle; it is a really simple "Entity", with only three verices.
*/
		class ENGINE_DECL_SPEC Triangle : public Shape
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
}