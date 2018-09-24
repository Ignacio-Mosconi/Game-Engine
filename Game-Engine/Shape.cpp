#include "Shape.h"
#include "Renderer.h"

Shape::Shape(Renderer* renderer, Material* material, unsigned int vertexCount) : Entity(renderer),
_material(material), _vertexBufferData(NULL), _vertexBufferID(-1), _vertexCount(vertexCount)
{
	cout << "Shape::Shape()" << endl;
}

Shape::~Shape()
{
	cout << "Shape::~Shape()" << endl;
}

bool Shape::create(float* vertexBufferData, unsigned int vertexComponents)
{
	cout << "Shape::create(vertexBufferData, vertexCount, vertexComponents)" << endl;

	if (_vertexBufferID != -1)
		dispose();

	int vertexBufferSize = sizeof(float) * _vertexCount * vertexComponents;

	_vertexBufferData = vertexBufferData;
	_vertexBufferID = _renderer->generateVertexBuffer(_vertexBufferData, vertexBufferSize);

	return _vertexBufferID != -1;
}

bool Shape::dispose()
{
	cout << "Shape::dispose()" << endl;

	bool wasDisposed = false;

	if (_vertexBufferID != -1)
	{
		_renderer->destroyVertexBuffer(_vertexBufferID);
		_vertexBufferData = NULL;
		_vertexBufferID = -1;

		wasDisposed = true;
	}

	return wasDisposed;
}
