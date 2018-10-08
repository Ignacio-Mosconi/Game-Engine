#include "Sprite.h"
#include "Sprite.h"
#include "Material.h"
#include "Renderer.h"

Sprite::Sprite(Renderer* renderer, Material* material) : Shape(renderer, material, 4)
{
	cout << "Sprite::Sprite()" << endl;
}

Sprite::~Sprite()
{
	cout << "Sprite::~Sprite()" << endl;
}

void Sprite::draw() const
{
	cout << "Sprite::draw()" << endl;

	Shape::draw();

	_renderer->enableAttribute(0);
	_renderer->enableAttribute(1);
	_renderer->bindBuffer(0, _vertexBufferID);
	_renderer->bindBuffer(1, _uvBufferID);
	_renderer->drawBuffer(TRIANGLE_STRIP, _vertexCount);
	_renderer->disableAttribute(0);
	_renderer->disableAttribute(1);
}

float* Sprite::setVertices(unsigned int vertexComponents) const
{
	cout << "Sprite::setVertices(vertexComponents)" << endl;

	float* vertexBufferData = new float[_vertexCount * vertexComponents]
	{
		-1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f
	};

	return vertexBufferData;
}

float* Sprite::setVerticesUV(float* uvBufferData) const
{
	cout << "Sprite::setVerticesUV(uvBufferData)" << endl;

	float* uvBufferData = new float[_vertexCount * 2]
	{
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f
	};

	return uvBufferData;
}