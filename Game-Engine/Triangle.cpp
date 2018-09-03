#include "Triangle.h"
#include "Renderer.h"

Triangle::Triangle(Renderer* renderer) : Entity(renderer)
{
	cout << "Triangle::Triangle()" << endl;
}

Triangle::~Triangle()
{
	cout << "Triangle::~Triangle()" << endl;
}

void Triangle::create(float* vertexBufferData, int vertexCount, int vertexComponents)
{
	cout << "Triangle::create(vertexBufferData, vertexCount, vertexComponents)" << endl;

	int vertexArraySize = sizeof(float) * vertexCount * vertexComponents;

	_vertexBufferData = vertexBufferData;
	_vertexCount = vertexCount;
	_vertexBufferID = _renderer->generateVertexBuffer(_vertexBufferData, vertexArraySize);
}

void Triangle::dispose()
{
	cout << "Triangle::dispose()" << endl;

	_vertexBufferData = NULL;
	_vertexCount = 0;
	_renderer->destroyVertexBuffer(_vertexBufferID);
}

void Triangle::draw() const
{
	cout << "Triangle::draw()" << endl;

	_renderer->draw(_vertexBufferID, _vertexCount);
}
