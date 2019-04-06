#include "Circle.h"
#include "Material.h"
#include "Renderer.h"

namespace gn
{
	Circle::Circle(Renderer* renderer, Material* material, unsigned int vertexCount) : Shape(renderer, material, vertexCount)
	{
		std::cout << "Circle::Circle()" << std::endl;
	}

	Circle::~Circle()
	{
		std::cout << "Circle::~Circle()" << std::endl;
	}

	void Circle::draw() const
	{
		Shape::draw();

		_renderer->enableAttribute(0);
		_renderer->bindBuffer(0, 3, _vertexBufferID);
		_renderer->drawBuffer(PrimitiveType::TRIANGLE_FAN, _vertexCount);
		_renderer->disableAttribute(0);
	}

	float* Circle::setVertices(unsigned int vertexComponents, float width, float height, float depth) const
	{
		float angle = 0;
		float* vertexBufferData = new float[_vertexCount * vertexComponents];

		for (unsigned int i = 0; i < _vertexCount * vertexComponents; i += vertexComponents)
		{
			vertexBufferData[i] = (float)width * cos(angle);
			vertexBufferData[i + 1] = (float)width * sin(angle);
			vertexBufferData[i + 2] = depth;

			angle += 2 * glm::pi<float>() / _vertexCount;
		}

		return vertexBufferData;
	}
}