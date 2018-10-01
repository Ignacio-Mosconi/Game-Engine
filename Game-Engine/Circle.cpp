#include "Circle.h"
#include "Material.h"
#include "Renderer.h"

Circle::Circle(Renderer* renderer, Material* material, unsigned int vertexCount) : 
Shape(renderer, material, vertexCount)
{
	cout << "Circle::Circle()" << endl;
}

Circle::~Circle()
{
	cout << "Circle::~Circle()" << endl;
}

void Circle::draw() const
{
	cout << "Circle::draw()" << endl;

	Shape::draw();

	_renderer->enableAttribute(0);
	_renderer->bindBuffer(0, _vertexBufferID);
	_renderer->drawBuffer(TRIANGLE_FAN, _vertexCount);
	_renderer->disableAttribute(0);
}
