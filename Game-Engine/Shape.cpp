#include "Shape.h"
#include "Renderer.h"
#include "Material.h"

namespace gn
{
	Shape::Shape(Renderer* renderer, Material* material, unsigned int vertexCount) : Entity(renderer),
	_material(material),
	_vertexBufferData(NULL), _colorBufferData(NULL),
	_vertexBufferID(-1), _colorBufferID(-1),
	_vertexCount(vertexCount)
	{
		std::cout << "Shape::Shape()" << std::endl;
	}

	Shape::~Shape()
	{
		std::cout << "Shape::~Shape()" << std::endl;
	}

	bool Shape::create(unsigned int vertexComponents, float* colorBufferData, float width, float height, float depth)
	{
		if (_vertexBufferID != -1)
			dispose();

		int vertexBufferSize = sizeof(float) * _vertexCount * vertexComponents;

		_vertexBufferData = setVertices(vertexComponents, width, height, depth);
		if (colorBufferData)
			_colorBufferData = setVerticesColor(colorBufferData, vertexComponents);

		_vertexBufferID = _renderer->generateVertexBuffer(_vertexBufferData, vertexBufferSize);
		_colorBufferID = (_colorBufferData) ? _renderer->generateVertexBuffer(_colorBufferData, vertexBufferSize) : -1;

		return _vertexBufferID != -1;
	}

	float* Shape::setVerticesColor(float* colorBufferData, unsigned int vertexComponents) const
	{
		int arrayLength = _vertexCount * vertexComponents;
		float* newColorBufferData = new float[arrayLength];

		for (unsigned int i = 0; i < arrayLength; i++)
			newColorBufferData[i] = colorBufferData[i];

		return newColorBufferData;
	}

	void Shape::dispose()
	{
		if (_vertexBufferID != -1)
		{
			_renderer->destroyVertexBuffer(_vertexBufferID);
			delete _vertexBufferData;
			_vertexBufferData = NULL;
			_vertexBufferID = -1;
		}

		if (_colorBufferID != -1)
		{
			_renderer->destroyVertexBuffer(_colorBufferID);
			delete _colorBufferData;
			_colorBufferData = NULL;
			_colorBufferID = -1;
		}
	}

	void Shape::draw() const
	{
		_renderer->loadIdentityMatrix();
		_renderer->setModelMatrix(_modelMatrix);

		if (_material)
		{
			_material->bind();
			_material->setMatrixProperty("MVP", _renderer->getMVP());
			_material->bindTexture();
		}
	}
}