#include "Circle.h"
#include "Material.h"
#include "Renderer.h"
#include <glm.hpp>
#include <gtc\constants.hpp>
using namespace glm;

Circle::Circle(Renderer* renderer, Material* material, unsigned int vertexCount) : Shape(renderer, material, vertexCount)
{
	cout << "Circle::Circle()" << endl;
}

Circle::~Circle()
{
	cout << "Circle::~Circle()" << endl;
}

void Circle::draw() const
{
	Shape::draw();

	_renderer->enableAttribute(0);
	_renderer->bindBuffer(0, 3, _vertexBufferID);
	_renderer->drawBuffer(TRIANGLE_FAN, _vertexCount);
	_renderer->disableAttribute(0);
}

float* Circle::setVertices(unsigned int vertexComponents,float width, float height) const
{
	float angle = 0;
	float* vertexBufferData = new float[_vertexCount * vertexComponents];

	for (unsigned int i = 0; i < _vertexCount * vertexComponents; i += vertexComponents)
	{
		vertexBufferData[i] = (float)width * cos(angle);
		vertexBufferData[i + 1] = (float)width * sin(angle);
		vertexBufferData[i + 2] = 0.0f;

		angle += 2 * pi<float>() / _vertexCount;
	}

	return vertexBufferData;
}
