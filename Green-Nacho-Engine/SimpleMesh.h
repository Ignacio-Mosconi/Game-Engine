#pragma once

#include <vector>
#include "Entity.h"
#include "Renderer.h"
#include "Material.h"
#include "Exports.h"

namespace gn
{
	class ENGINE_API SimpleMesh : public Entity
	{
	protected:
		Material* _material;

		float* _vertexBufferData;
		float* _colorBufferData;
		std::vector<unsigned short> _indexBufferData;

		unsigned int _vertexBufferID;
		unsigned int _colorBufferID;
		unsigned int _indexBufferID;
		
		unsigned int _vertexCount;

		bool create(float* colorBufferData = NULL);

		virtual float* generateVertices() const = 0;
		virtual std::vector<unsigned short> generateVerticesIndexes() const = 0;

	public:
		SimpleMesh(Renderer* renderer, Material* material, unsigned int vertexCount);
		virtual ~SimpleMesh();

		float* generateVerticesColors(float* colorBufferData) const;

		virtual void dispose();

		virtual void draw() const = 0;

		inline Material* getMaterial() const { return _material; }
	};
}