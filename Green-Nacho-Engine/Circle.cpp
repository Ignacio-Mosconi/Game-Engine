#include "Circle.h"
#include "Material.h"
#include "Renderer.h"

namespace gn
{
	Circle::Circle(Renderer* renderer, Material* material, unsigned int vertexCount, float radius, float* colorBufferData) : 
	Shape(renderer, material), _vertexCount(vertexCount), _radius(radius)
	{
		create(vertexCount, colorBufferData);
	}

	Circle::~Circle()
	{
		dispose();
	}

	void Circle::draw() const
	{
		Shape::draw();

		_renderer->enableAttribute(0);
		_renderer->enableAttribute(1);
		_renderer->bindBuffer(0, VERTEX_COMPONENTS, _vertexBufferID);
		_renderer->bindBuffer(1, VERTEX_COMPONENTS, _colorBufferID);
		_renderer->drawBuffer(PrimitiveType::TRIANGLE_FAN, _vertexCount);
		_renderer->disableAttribute(0);
		_renderer->disableAttribute(1);
	}

	float* Circle::generateVertexBufferData() const
	{
		float angle = 0;
		float* vertexBufferData = new float[_vertexCount * VERTEX_COMPONENTS];

		for (unsigned int i = 0; i < _vertexCount * VERTEX_COMPONENTS; i += VERTEX_COMPONENTS)
		{
			vertexBufferData[i] = _radius * glm::cos(angle);
			vertexBufferData[i + 1] = _radius * glm::sin(angle);
			vertexBufferData[i + 2] = 0.0f;

			angle += 2 * glm::pi<float>() / _vertexCount;
		}

		return vertexBufferData;
	}
}