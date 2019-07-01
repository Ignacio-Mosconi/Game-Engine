#pragma once

#include <vector>
#include "Shape.h"
#include "Exports.h"

namespace gn
{
	namespace legacy
	{
		class ENGINE_DECL_SPEC Mesh : public Shape
		{
		protected:
			std::vector<unsigned int> _indexBufferData;

			unsigned int _indexBufferID;

			virtual bool create(unsigned int vertexCount, float* colorBufferData = NULL) override;

			virtual float* generateVertexBufferData() const = 0;
			virtual std::vector<unsigned int> generateIndexBufferData() const = 0;

		public:
			Mesh(Renderer* renderer, Material* material);
			virtual ~Mesh();

			virtual void dispose() override;

			virtual void draw() const = 0;
		};
	}
}