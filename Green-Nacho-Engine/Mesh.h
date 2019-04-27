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
		std::vector<unsigned short> _indexBufferData;

		unsigned int _vertexBufferID;
		unsigned int _colorBufferID;
		unsigned int _indexBufferID;
		
		unsigned int _vertexCount;

		virtual bool create(float* colorBufferData = NULL);
		virtual float* setVertices() const = 0;
		virtual std::vector<unsigned short> setVerticesIndexes() const = 0;
		
		float* setVerticesColors(float* colorBufferData) const;

	public:
		Mesh(Renderer* renderer, Material* material, unsigned int vertexCount);
		virtual ~Mesh();

		virtual void dispose();

		virtual void draw() const = 0;

		inline Material* getMaterial() const { return _material; }
	};
}