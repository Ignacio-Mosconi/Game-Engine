#pragma once

#include "SimpleMesh.h"

namespace gn
{
	/*
		A "Mesh" that represents a tridimensional object; it is composed of 8 vertices, thanks to the use of an index buffer.
	*/
	class ENGINE_API Cube : public SimpleMesh
	{
	private:
		float _width;
		float _height;
		float _depth;

		float* generateVertices() const override;
		std::vector<unsigned short> generateVerticesIndexes() const override;

	public:
		Cube(Renderer* renderer, Material* material, float _width, float _height, float _depth);
		~Cube();
		
		void setFaceColors(float front[VERTEX_COMPONENTS], float back[VERTEX_COMPONENTS]);

		void draw() const override;
	};
}
