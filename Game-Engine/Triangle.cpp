#include "Triangle.h"
#include "Renderer.h"

Triangle::Triangle(Renderer* renderer) : Entity(renderer)
{

}

Triangle::~Triangle()
{

}

bool Triangle::create(float& vertexBufferData, int vertexCount, int vertexComponents)
{
	int vertexArraySize = sizeof(float) * vertexCount * vertexComponents;

	_vertexBufferData = vertexBufferData;
	_vertexCount = vertexCount;
	_vertexBufferID = _renderer->generateVertexBuffer(_vertexBufferData, vertexArraySize);

	return _vertexBufferData;
}

void Triangle::dispose()
{
	_vertexBufferData = NULL;
	_vertexCount = 0;
	_renderer->destroyVertexBuffer(_vertexBufferID);
}

void Triangle::draw() const
{
	_renderer->draw(_vertexBufferID, _vertexCount);
}
