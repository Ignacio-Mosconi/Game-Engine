#include "Legacy/Triangle.h"
#include "Core/Material.h"
#include "Core/Renderer.h"

namespace gn
{
	namespace legacy
	{
		Triangle::Triangle(Renderer* renderer, Material* material, float base, float height, float* colorBufferData) :
			Shape(renderer, material), _base(base), _height(height)
		{
			create(TRIANGLE_VERTICES, colorBufferData);
		}

		Triangle::~Triangle()
		{
			dispose();
		}

		void Triangle::draw() const
		{
			Shape::draw();

			_renderer->enableAttribute(0);
			_renderer->enableAttribute(1);
			_renderer->bindBuffer(0, VERTEX_COMPONENTS, _vertexBufferID);
			_renderer->bindBuffer(1, VERTEX_COMPONENTS, _colorBufferID);
			_renderer->drawBuffer(PrimitiveType::TRIANGLE, TRIANGLE_VERTICES);
			_renderer->disableAttribute(0);
			_renderer->disableAttribute(1);
		}

		float* Triangle::generateVertexBufferData() const
		{
			float valueX = _base * 0.5f;
			float valueY = _height * 0.5f;

			float* vertexBufferData = new float[TRIANGLE_VERTICES * VERTEX_COMPONENTS]
			{
				-valueX, -valueY, 0.0f,
				valueX, -valueY, 0.0f,
				0.0f, valueY, 0.0f
			};

			return vertexBufferData;
		}
	}
}