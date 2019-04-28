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

		virtual bool create(unsigned int vertexCount, float* colorBufferData = NULL);

		virtual float* generateVertexBufferData() const = 0;
		virtual float* generateColorBufferData(float* colorBufferData, unsigned int vertexCount) const;

	public:
		Shape(Renderer* renderer, Material* material);
		virtual ~Shape();

		virtual void dispose();

		virtual void draw() const = 0;

		inline Material* getMaterial() const { return _material;  }
	};
}