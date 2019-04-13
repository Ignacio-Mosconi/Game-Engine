#include "Rectangle.h"
#include "Material.h"
#include "Renderer.h"

namespace gn
{
	Rectangle::Rectangle(Renderer* renderer, Material* material) : Shape(renderer, material, 4)
	{
		std::cout << "Rectangle::Rectangle()" << std::endl;
	}

	Rectangle::~Rectangle()
	{
		std::cout << "Rectangle::~Rectangle()" << std::endl;
	}

	void Rectangle::draw() const
	{
		Shape::draw();

		_renderer->enableAttribute(0);
		_renderer->enableAttribute(1);
		_renderer->bindBuffer(0, 3, _vertexBufferID);
		_renderer->bindBuffer(1, 3, _colorBufferID);
		_renderer->drawBuffer(PrimitiveType::TRIANGLE_STRIP, _vertexCount);
		_renderer->disableAttribute(0);
		_renderer->disableAttribute(1);
	}

	float* Rectangle::setVertices(unsigned int vertexComponents, float width, float height) const
	{
		float valueX = width * 0.5f;
		float valueY = height * 0.5f;

		float* vertexBufferData = new float[_vertexCount * vertexComponents]
		{
			-valueX, -valueY, 0.0f,
			-valueX, valueY, 0.0f,
			valueX, -valueY, 0.0f,
			valueX, valueY, 0.0f
		};

		return vertexBufferData;
	}
}