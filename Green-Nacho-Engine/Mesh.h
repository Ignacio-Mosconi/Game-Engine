#pragma once

#include <vector>

#include "Shape.h"
#include "Exports.h"

namespace gn
{
	class ENGINE_API Mesh : public Shape
	{
	protected:
		std::vector<unsigned short> _indexBufferData;

		unsigned int _indexBufferID;

		bool create(unsigned int vertexCount, float* colorBufferData = NULL) override;
		
		virtual float* generateVertexBufferData() const = 0;
		virtual std::vector<unsigned short> generateIndexBufferData() const = 0;

	public:
		Mesh(Renderer* renderer, Material* material);
		virtual ~Mesh();

		void dispose() override;

		virtual void draw() const = 0;
	};
}