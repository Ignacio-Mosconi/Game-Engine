#include "Triangle.h"
#include "Material.h"
#include "Renderer.h"

Triangle::Triangle(Renderer* renderer, Material* material) : Entity(renderer), 
_material(material), _vertexBufferData(NULL), _vertexBufferID(-1), _vertexCount(0)
{
	cout << "Triangle::Triangle()" << endl;
}

Triangle::~Triangle()
{
	cout << "Triangle::~Triangle()" << endl;
}

bool Triangle::create(float* vertexBufferData, int vertexCount, int vertexComponents)
{
	cout << "Triangle::create(vertexBufferData, vertexCount, vertexComponents)" << endl;

	if (_vertexBufferID != -1)
		dispose();

	int vertexBufferSize = sizeof(float) * vertexCount * vertexComponents;

	_vertexBufferData = vertexBufferData;
	_vertexCount = vertexCount;
	_vertexBufferID = _renderer->generateVertexBuffer(_vertexBufferData, vertexBufferSize);

	return _vertexBufferID != -1;
}

bool Triangle::dispose()
{
	cout << "Triangle::dispose()" << endl;

	bool wasDisposed = false;

	if (_vertexBufferID != -1)
	{
		_renderer->destroyVertexBuffer(_vertexBufferID);
		_vertexBufferData = NULL;
		_vertexBufferID = -1;
		_vertexCount = 0;

		wasDisposed = true;
	}

	return wasDisposed;
}

void Triangle::draw() const
{
	cout << "Triangle::draw()" << endl;

	_renderer->loadIdentityMatrix();
	_renderer->setModelMatrix(_model);

	if (_material)
	{
		_material->bind();
		_material->setMatrixProperty("MVP", _renderer->getMVP());
	}
	
	_renderer->drawBuffer(_vertexBufferID, _vertexCount);
}
