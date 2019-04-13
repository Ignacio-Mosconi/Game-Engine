#pragma once

#include "Entity.h"

namespace gn
{
	class Material;
/*
	It consists of the base class for many of the entities that will be actually drawn to the screen.
*/
	class ENGINE_API Shape : public Entity
	{
	protected:
		Material* _material;
	
		float* _vertexBufferData;
		float* _colorBufferData;
	
		unsigned int _vertexBufferID;
		unsigned int _colorBufferID;
		
		unsigned int _vertexCount;

	public:
		Shape(Renderer* renderer, Material* material, unsigned int vertexCount);
		virtual ~Shape();

		virtual bool create(unsigned int vertexComponents, float* colorBufferData = NULL, float width = 1.0f, float height = 1.0f);
		virtual float* setVertices(unsigned int vertexComponents, float width = 1.0f, float height = 1.0f) const = 0;
		virtual float* setVerticesColor(float* colorBufferData, unsigned int vertexComponents) const;
	
		virtual void dispose();

		virtual void draw() const = 0;

		inline Material* getMaterial() const { return _material;  }
	};
}