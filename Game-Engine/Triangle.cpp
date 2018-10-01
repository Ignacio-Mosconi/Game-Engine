#include "Triangle.h"
#include "Material.h"
#include "Renderer.h"

Triangle::Triangle(Renderer* renderer, Material* material) : Shape(renderer, material, 3)
{
	cout << "Triangle::Triangle()" << endl;
}

Triangle::~Triangle()
{
	cout << "Triangle::~Triangle()" << endl;
}

void Triangle::draw() const
{
	cout << "Triangle::draw()" << endl;
	
	Shape::draw();

	_renderer->enableAttribute(0);
	_renderer->bindBuffer(0, _vertexBufferID);
	_renderer->drawBuffer(TRIANGLE, _vertexCount);
	_renderer->disableAttribute(0);
}

float* Triangle::setVertices(unsigned int vertexComponents) const
{
	cout << "Triangle::setVertices(vertexComponents)" << endl;

	float* vertexBufferData = new float[_vertexCount * vertexComponents]
	{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	return vertexBufferData;
}
