#pragma once

#include "Mesh.h"

namespace gn
{
	/*
		A "Mesh" that represents a tridimensional object; it is composed of 8 vertices, thanks to the use of an index buffer.
	*/
	class ENGINE_API Cube : public Mesh
	{
	public:
		Cube(Renderer* renderer, Material* material);
		~Cube();

		float* setVertices(unsigned int vertexComponents, float width = 1.0f, float height = 1.0f, float depth = 1.0f) const override;
		std::vector<unsigned short> setVerticesIndexes() const override;
		void setFaceColors(float front[3], float back[3], float left[3], float right[3], float bottom[3], float top[3]);

		void draw() const override;
	};
}
