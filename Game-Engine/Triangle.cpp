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

	_renderer->loadIdentityMatrix();
	_renderer->setModelMatrix(_modelMatrix);

	if (_material)
	{
		_material->bind();
		_material->setMatrixProperty("MVP", _renderer->getMVP());
	}
	
	_renderer->enableAttribute(0);
	_renderer->bindBuffer(0, _vertexBufferID);
	_renderer->drawBuffer(_vertexCount);
	_renderer->disableAttribute(0);
}
