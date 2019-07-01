#include "Rectangle.h"
#include "Material.h"
#include "Renderer.h"

namespace gn
{
	namespace legacy
	{
		Rectangle::Rectangle(Renderer* renderer, Material* material, float width, float height, float *colorBufferData) :
			Shape(renderer, material), _width(width), _height(height)
		{
			create(RECTANGLE_VERTICES, colorBufferData);
		}

		Rectangle::~Rectangle()
		{
			dispose();
		}

		void Rectangle::draw() const
		{
			Shape::draw();

			_renderer->enableAttribute(0);
			_renderer->enableAttribute(1);
			_renderer->bindBuffer(0, VERTEX_COMPONENTS, _vertexBufferID);
			_renderer->bindBuffer(1, VERTEX_COMPONENTS, _colorBufferID);
			_renderer->drawBuffer(PrimitiveType::TRIANGLE_STRIP, RECTANGLE_VERTICES);
			_renderer->disableAttribute(0);
			_renderer->disableAttribute(1);
		}

		float* Rectangle::generateVertexBufferData() const
		{
			float valueX = _width * 0.5f;
			float valueY = _height * 0.5f;

			float* vertexBufferData = new float[RECTANGLE_VERTICES * VERTEX_COMPONENTS]
			{
				-valueX, -valueY, 0.0f,
				-valueX, valueY, 0.0f,
				valueX, -valueY, 0.0f,
				valueX, valueY, 0.0f
			};

			return vertexBufferData;
		}
	}
}