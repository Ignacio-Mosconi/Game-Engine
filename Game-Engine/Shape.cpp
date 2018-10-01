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

bool Shape::create(unsigned int vertexComponents, float* colorBufferData)
{
	cout << "Shape::create(vertexComponents, colorBufferData)" << endl;

	if (_vertexBufferID != -1)
		dispose();

	int vertexBufferSize = sizeof(float) * _vertexCount * vertexComponents;

	_vertexBufferData = setVertices(vertexComponents);
	if (colorBufferData)
		_colorBufferData = setVerticesColor(colorBufferData, vertexComponents);

	_vertexBufferID = _renderer->generateVertexBuffer(_vertexBufferData, vertexBufferSize);
	_colorBufferID = _renderer->generateVertexBuffer(_colorBufferData, vertexBufferSize);

	return _vertexBufferID != -1;
}

float* Shape::setVerticesColor(float* colorBufferData, unsigned int vertexComponents) const
{
	cout << "Shape::setVerticesColor(colorBufferData, vertexComponents)" << endl;

	int arrayLength = _vertexCount * vertexComponents;
	float* newColorBufferData = new float[arrayLength];

	for (unsigned int i = 0; i <arrayLength; i++)
		newColorBufferData[i] = colorBufferData[i];

	return newColorBufferData;
}

bool Shape::dispose()
{
	cout << "Shape::dispose()" << endl;

	bool wasDisposed = false;

	if (_vertexBufferID != -1)
	{
		_renderer->destroyVertexBuffer(_vertexBufferID);
		delete _vertexBufferData;
		if (_colorBufferData)
			delete _colorBufferData;
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
