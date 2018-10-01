#include "Shape.h"
#include "Renderer.h"
#include "Material.h"

Shape::Shape(Renderer* renderer, Material* material, unsigned int vertexCount) : Entity(renderer),
_material(material), _vertexBufferData(NULL), _colorBufferData(NULL), _vertexBufferID(-1), _colorBufferID(-1),
_vertexCount(vertexCount)
{
	cout << "Shape::Shape()" << endl;
}

Shape::~Shape()
{
	cout << "Shape::~Shape()" << endl;
}

bool Shape::create(float* vertexBufferData, float* colorBufferData, unsigned int vertexComponents)
{
	cout << "Shape::create(vertexBufferData, colorVertexData, vertexComponents)" << endl;

	if (_vertexBufferID != -1)
		dispose();

	int vertexBufferSize = sizeof(float) * _vertexCount * vertexComponents;

	_vertexBufferData = vertexBufferData;
	_colorBufferData = colorBufferData;

	_vertexBufferID = _renderer->generateVertexBuffer(_vertexBufferData, vertexBufferSize);
	_colorBufferID = _renderer->generateVertexBuffer(_colorBufferData, vertexBufferSize);

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
		_colorBufferData = NULL;
		_vertexBufferID = -1;
		_colorBufferID = -1;

		wasDisposed = true;
	}

	return wasDisposed;
}

void Shape::draw() const
{
	cout << "Shape::draw()" << endl;

	_renderer->loadIdentityMatrix();
	_renderer->setModelMatrix(_modelMatrix);

	if (_material)
	{
		_material->bind();
		_material->setMatrixProperty("MVP", _renderer->getMVP());
	}
}
