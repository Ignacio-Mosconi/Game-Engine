#include "Rectangle.h"
#include "Material.h"
#include "Renderer.h"

Rectangle::Rectangle(Renderer* renderer, Material* material) : Shape(renderer, material, 4)
{
	cout << "Rectangle::Rectangle()" << endl;
}

Rectangle::~Rectangle()
{
	cout << "Rectangle::~Rectangle()" << endl;
}

void Rectangle::draw() const
{
	Shape::draw();

	_renderer->enableAttribute(0);
	_renderer->enableAttribute(1);
	_renderer->bindBuffer(0, 3, _vertexBufferID);
	_renderer->bindBuffer(1, 3, _colorBufferID);
	_renderer->drawBuffer(TRIANGLE_STRIP, _vertexCount);
	_renderer->disableAttribute(0);
	_renderer->disableAttribute(1);
}

float* Rectangle::setVertices(unsigned int vertexComponents, float width, float height) const
{
	float valueX = (float)width / 2;
	float valueY = (float)height / 2;

	float* vertexBufferData = new float[_vertexCount * vertexComponents]
	{
		-valueX, -valueY, 0.0f,
		-valueX, valueY, 0.0f,
		valueX, -valueY, 0.0f,
		valueX, valueY, 0.0f
	};

	return vertexBufferData;
}