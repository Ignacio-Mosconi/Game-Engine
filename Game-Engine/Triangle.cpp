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
		_renderer->drawBuffer(TRIANGLE, _vertexCount);
		_renderer->disableAttribute(0);
	}

	float* Triangle::setVertices(unsigned int vertexComponents, float width, float height) const
	{
		float valueX = (float)width / 2;
		float valueY = (float)height / 2;

		float* vertexBufferData = new float[_vertexCount * vertexComponents]
		{
			-valueX, -valueY, 0.0f,
			valueX, -valueY, 0.0f,
			0.0f, valueY, 0.0f
		};

		return vertexBufferData;
	}
}