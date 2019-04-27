#include "Mesh.h"
#include "Renderer.h"
#include "Material.h"

namespace gn
{
	Mesh::Mesh(Renderer* renderer, Material* material, unsigned int vertexCount) : Entity(renderer),
	_material(material),
	_vertexBufferData(NULL), _colorBufferData(NULL), _indexBufferData(NULL),
	_vertexBufferID(-1), _colorBufferID(-1), _indexBufferID(-1),
	_vertexCount(vertexCount)
	{

	}

	Mesh::~Mesh()
	{

	}

	bool Mesh::create(float* colorBufferData)
	{
		if (_vertexBufferID != -1)
			dispose();

		_vertexBufferData = setVertices();
		_colorBufferData = (colorBufferData) ? setVerticesColors(colorBufferData) : NULL;
		_indexBufferData = setVerticesIndexes();

		int vertexBufferSize = sizeof(float) * _vertexCount * VERTEX_COMPONENTS_3D;
		int indexBufferSize = sizeof(unsigned short) * _indexBufferData.size();

		_vertexBufferID = _renderer->generateVertexBuffer(_vertexBufferData, vertexBufferSize);
		_colorBufferID = (_colorBufferData) ? _renderer->generateVertexBuffer(_colorBufferData, vertexBufferSize) : -1;
		_indexBufferID = _renderer->generateIndexBuffer(_indexBufferData, indexBufferSize);

		return (_vertexBufferID != -1);
	}

	float* Mesh::setVerticesColors(float* colorBufferData) const
	{
		int arrayLength = _vertexCount * VERTEX_COMPONENTS_3D;
		float* newColorBufferData = new float[arrayLength];

		for (unsigned int i = 0; i < arrayLength; i++)
			newColorBufferData[i] = colorBufferData[i];

		return newColorBufferData;
	}

	void Mesh::dispose()
	{
		if (_vertexBufferID != -1)
		{
			_renderer->destroyBuffer(_vertexBufferID);
			delete _vertexBufferData;
			_vertexBufferData = NULL;
			_vertexBufferID = -1;
		}

		if (_colorBufferID != -1)
		{
			_renderer->destroyBuffer(_colorBufferID);
			delete _colorBufferData;
			_colorBufferData = NULL;
			_colorBufferID = -1;
		}

		if (_indexBufferID != -1)
		{
			_renderer->destroyBuffer(_indexBufferID);
			_indexBufferID = -1;
		}
	}

	void Mesh::draw() const
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