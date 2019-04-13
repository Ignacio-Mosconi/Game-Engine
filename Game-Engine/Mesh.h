#pragma once

#include <vector>
#include "Entity.h"
#include "Material.h"
#include "Exports.h"

namespace gn
{
	class ENGINE_API Mesh : public Entity
	{
	protected:
		Material* _material;

		float* _vertexBufferData;
		float* _colorBufferData;
		std::vector<unsigned short>* _indexBufferData;

		unsigned int _vertexBufferID;
		unsigned int _colorBufferID;
		unsigned int _indexBufferID;
		unsigned int _vertexCount;

	public:
		Mesh(Renderer* renderer, Material* material, unsigned int vertexCount);
		virtual ~Mesh();

		virtual bool create(unsigned int vertexComponents, float* colorBufferData = NULL,
			float width = 1.0f, float height = 1.0f, float depth = 0.0f);
		virtual float* setVertices(unsigned int vertexComponents, float width = 1.0f, float height = 1.0f, float depth = 0.0f) const = 0;
		virtual std::vector<unsigned short>* setVerticesIndexes() const = 0;
		virtual float* setVerticesColor(float* colorBufferData, unsigned int vertexComponents) const;

		virtual void dispose();

		virtual void draw() const = 0;

		inline Material* getMaterial() const { return _material; }
	};
}