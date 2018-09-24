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

	_renderer->loadIdentityMatrix();
	_renderer->setModelMatrix(_modelMatrix);

	if (_material)
	{
		_material->bind();
		_material->setMatrixProperty("MVP", _renderer->getMVP());
	}

	_renderer->enableAttribute(0);
	_renderer->enableAttribute(1);
	_renderer->bindBuffer(0, _vertexBufferID);
	_renderer->drawBuffer(_vertexCount);
	_renderer->disableAttribute(0);
	_renderer->disableAttribute(1);
}

