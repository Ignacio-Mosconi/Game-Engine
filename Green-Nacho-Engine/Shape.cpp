#include "Shape.h"
#include "Renderer.h"
#include "Material.h"

namespace gn
{
	namespace legacy
	{
		Shape::Shape(Renderer* renderer, Material* material) : Entity(renderer),
			_material(material),
			_vertexBufferData(NULL), _colorBufferData(NULL),
			_vertexBufferID(-1), _colorBufferID(-1)
		{
		}

		Shape::~Shape()
		{
		}

		bool Shape::create(unsigned int vertexCount, float* colorBufferData)
		{
			if (_vertexBufferID != (unsigned int)-1)
				dispose();

			_vertexBufferData = generateVertexBufferData();
			if (colorBufferData)
				_colorBufferData = generateColorBufferData(colorBufferData, vertexCount);

			int vertexBufferSize = sizeof(float) * vertexCount * VERTEX_COMPONENTS;

			_vertexBufferID = _renderer->generateVertexBuffer(_vertexBufferData, vertexBufferSize);
			_colorBufferID = (_colorBufferData) ? _renderer->generateVertexBuffer(_colorBufferData, vertexBufferSize) : -1;

			return (_vertexBufferID != -1);
		}

		float* Shape::generateColorBufferData(float* colorBufferData, unsigned int vertexCount) const
		{
			int arrayLength = vertexCount * VERTEX_COMPONENTS;
			float* newColorBufferData = new float[arrayLength];

			for (int i = 0; i < arrayLength; i++)
				newColorBufferData[i] = colorBufferData[i];

			return newColorBufferData;
		}

		void Shape::dispose()
		{
			if (_vertexBufferID != (unsigned int)-1)
			{
				_renderer->destroyBuffer(_vertexBufferID);
				delete[] _vertexBufferData;
				_vertexBufferData = NULL;
				_vertexBufferID = -1;
			}

			if (_colorBufferID != (unsigned int)-1)
			{
				_renderer->destroyBuffer(_colorBufferID);
				delete[] _colorBufferData;
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
}