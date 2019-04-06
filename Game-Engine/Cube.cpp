#include "Cube.h"
#include "Material.h"
#include "Renderer.h"

namespace gn
{
	Cube::Cube(Renderer* renderer, Material* material) : Shape(renderer, material, 36)
	{
		std::cout << "Cube::Cube()" << std::endl;
	}

	Cube::~Cube()
	{
		std::cout << "Cube::~Cube()" << std::endl;
	}

	void Cube::draw() const
	{
		Shape::draw();

		_renderer->enableAttribute(0);
		_renderer->enableAttribute(1);
		_renderer->bindBuffer(0, 3, _vertexBufferID);
		_renderer->bindBuffer(1, 3, _colorBufferID);
		_renderer->drawBuffer(TRIANGLE, _vertexCount);
		_renderer->disableAttribute(0);
		_renderer->disableAttribute(1);
	}

	float* Cube::setVertices(unsigned int vertexComponents, float width, float height, float depth) const
	{
		float valueX = width * 0.5f;
		float valueY = height * 0.5f;
		float valueZ = depth * 0.5f;

		float* vertexBufferData = new float[_vertexCount * vertexComponents]
		{
			-valueX, -valueY, -valueZ,
			-valueX, -valueY, valueZ,
			-valueX, valueY, valueZ,

			valueX, valueY, -valueZ, 
			-valueX, -valueY, -valueZ,
			-valueX, valueY, -valueZ,

			valueX, -valueY, valueZ,
			-valueX, -valueY, -valueZ,
			valueX, -valueY, -valueZ,

			valueX, valueY, -valueZ,
			valueX, -valueY, -valueZ,
			-valueX, -valueY, -valueZ,

			-valueX, -valueY, -valueZ,
			-valueX, valueY, valueZ,
			-valueX, valueY, -valueZ,

			valueX, -valueY, valueZ
			-valueX, -valueY, valueZ,
			-valueX, -valueY, -valueZ,

			-valueX, valueY, valueZ,
			-valueX, -valueY, valueZ,
			valueX, -valueY, valueZ,

			valueX, valueY, valueZ,
			valueX, -valueY, -valueZ,
			valueX, valueY, -valueZ,

			valueX, -valueY, -valueZ,
			valueX, valueY, valueZ,
			valueX, -valueY, valueZ,

			valueX, valueY, valueZ,
			valueX, valueY, -valueZ,
			-valueX, valueY, -valueZ,

			valueX, valueY, valueZ,
			-valueX, valueY, -valueZ,
			-valueX, valueY, valueZ,

			valueX, valueY, valueZ,
			-valueX, valueY, valueZ,
			valueX, -valueY, valueZ
		};

		return vertexBufferData;
	}
}