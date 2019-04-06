#include "Triangle.h"
#include "Material.h"
#include "Renderer.h"

namespace gn
{
	Triangle::Triangle(Renderer* renderer, Material* material) : Shape(renderer, material, 3)
	{
		std::cout << "Triangle::Triangle()" << std::endl;
	}

	Triangle::~Triangle()
	{
		std::cout << "Triangle::~Triangle()" << std::endl;
	}

	void Triangle::draw() const
	{
		Shape::draw();

		_renderer->enableAttribute(0);
		_renderer->bindBuffer(0, 3, _vertexBufferID);
		_renderer->drawBuffer(PrimitiveType::TRIANGLE, _vertexCount);
		_renderer->disableAttribute(0);
	}

	float* Triangle::setVertices(unsigned int vertexComponents, float width, float height, float depth) const
	{
		float valueX = width * 0.5f;
		float valueY = height * 0.5f;

		float* vertexBufferData = new float[_vertexCount * vertexComponents]
		{
			-valueX, -valueY, depth,
			valueX, -valueY, depth,
			0.0f, valueY, depth
		};

		return vertexBufferData;
	}
}