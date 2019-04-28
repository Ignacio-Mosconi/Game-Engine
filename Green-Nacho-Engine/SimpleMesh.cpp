#include "SimpleMesh.h"

namespace gn
{
	SimpleMesh::SimpleMesh(Renderer* renderer, Material* material, unsigned int vertexCount) : Entity(renderer),
	_material(material),
	_vertexBufferData(NULL), _colorBufferData(NULL), _indexBufferData(NULL),
	_vertexBufferID(-1), _colorBufferID(-1), _indexBufferID(-1),
	_vertexCount(vertexCount)
	{

	}

	SimpleMesh::~SimpleMesh()
	{

	}

	bool SimpleMesh::create(float* colorBufferData)
	{
		if (_vertexBufferID != -1)
			dispose();

		_vertexBufferData = generateVertices();
		_colorBufferData = (colorBufferData) ? generateVerticesColors(colorBufferData) : NULL;
		_indexBufferData = generateVerticesIndexes();

		int vertexBufferSize = sizeof(float) * _vertexCount * VERTEX_COMPONENTS;
		int indexBufferSize = sizeof(unsigned short) * _indexBufferData.size();

		_vertexBufferID = _renderer->generateVertexBuffer(_vertexBufferData, vertexBufferSize);
		_colorBufferID = (_colorBufferData) ? _renderer->generateVertexBuffer(_colorBufferData, vertexBufferSize) : -1;
		_indexBufferID = _renderer->generateIndexBuffer(_indexBufferData, indexBufferSize);

		return (_vertexBufferID != -1);
	}

	float* SimpleMesh::generateVerticesColors(float* colorBufferData) const
	{
		int arrayLength = _vertexCount * VERTEX_COMPONENTS;
		float* newColorBufferData = new float[arrayLength];

		for (unsigned int i = 0; i < arrayLength; i++)
			newColorBufferData[i] = colorBufferData[i];

		return newColorBufferData;
	}

	void SimpleMesh::dispose()
	{
		if (_vertexBufferID != -1)
		{
			_renderer->destroyBuffer(_vertexBufferID);
			delete[] _vertexBufferData;
			_vertexBufferData = NULL;
			_vertexBufferID = -1;
		}

		if (_colorBufferID != -1)
		{
			_renderer->destroyBuffer(_colorBufferID);
			delete[] _colorBufferData;
			_colorBufferData = NULL;
			_colorBufferID = -1;
		}

		if (_indexBufferID != -1)
		{
			_renderer->destroyBuffer(_indexBufferID);
			_indexBufferID = -1;
		}
	}

	void SimpleMesh::draw() const
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