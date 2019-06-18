#include "Mesh.h"
#include "Renderer.h"

namespace gn
{
	Mesh::Mesh(Renderer* renderer, Material* material) : Shape(renderer, material),
	_indexBufferID(-1)
	{
	}

	Mesh::~Mesh()
	{
	}

	bool Mesh::create(unsigned int vertexCount, float* colorBufferData)
	{
		_indexBufferData = generateIndexBufferData();

		int indexBufferSize = sizeof(unsigned int) * (int)_indexBufferData.size();

		_indexBufferID = _renderer->generateIndexBuffer(_indexBufferData, indexBufferSize);

		return (Shape::create(vertexCount, colorBufferData));
	}

	void Mesh::dispose()
	{
		Shape::dispose();

		if (_indexBufferID != (unsigned int)-1)
		{
			_renderer->destroyBuffer(_indexBufferID);
			_indexBufferID = -1;
		}
	}
}