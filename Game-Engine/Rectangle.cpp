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
	cout << "Rectangle::draw()" << endl;

	Shape::draw();

	_renderer->enableAttribute(0);
	_renderer->enableAttribute(1);
	_renderer->bindBuffer(0, _vertexBufferID);
	_renderer->bindBuffer(1, _colorBufferID);
	_renderer->drawBuffer(TRIANGLE_STRIP, _vertexCount);
	_renderer->disableAttribute(0);
	_renderer->disableAttribute(1);
}

float* Rectangle::setVertices(unsigned int vertexComponents) const
{
	cout << "Rectangle::setVertices(vertexComponents)" << endl;

	float* vertexBufferData = new float[_vertexCount * vertexComponents]
	{
		-1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f
	};

	return vertexBufferData;
}