#pragma once

#include "Mesh.h"

namespace gn
{
	/*
		A "Mesh" that represents a tridimensional figure; it is composed of 8 vertices, thanks to the use of an index buffer.
	*/
	class ENGINE_DECL_SPEC Cube : public Mesh
	{
	private:
		float _width;
		float _height;
		float _depth;
	
	protected:
		float* generateVertexBufferData() const override;
		std::vector<unsigned int> generateIndexBufferData() const override;

	public:
		Cube(Renderer* renderer, Material* material, float _width = 1.0f, float _height = 1.0f, float _depth = 1.0f, 
			float* colorBufferData = NULL);
		~Cube();
		
		void setFaceColors(float front[VERTEX_COMPONENTS], float back[VERTEX_COMPONENTS]);

		void draw() const override;
	};
}
