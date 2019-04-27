#pragma once

#include "Mesh.h"

namespace gn
{
	/*
		A "Mesh" that represents a tridimensional object; it is composed of 8 vertices, thanks to the use of an index buffer.
	*/
	class ENGINE_API Cube : public Mesh
	{
	private:
		float _width;
		float _height;
		float _depth;

	public:
		Cube(Renderer* renderer, Material* material, float _width, float _height, float _depth);
		~Cube();

		float* setVertices() const override;
		std::vector<unsigned short> setVerticesIndexes() const override;
		
		void setFaceColors(float front[VERTEX_COMPONENTS_3D], float back[VERTEX_COMPONENTS_3D]);

		void draw() const override;
	};
}
