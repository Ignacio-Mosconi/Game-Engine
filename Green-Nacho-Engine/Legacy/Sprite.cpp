#include "Legacy/Sprite.h"
#include "Core/Material.h"
#include "Core/Renderer.h"

namespace gn
{
	namespace legacy
	{
		Sprite::Sprite(Renderer* renderer, Material* material, float frameWidth, float frameHeight, unsigned int rows, unsigned int columns) :
			Shape(renderer, material),
			_uvBufferData(NULL), _uvBufferID(-1),
			_frameID(0), _rows(0), _columns(0), _frameWidth(0), _frameHeight(0)
		{
			setFramesInfo(rows, columns, frameWidth, frameHeight);
			create(RECTANGLE_VERTICES);
		}

		Sprite::~Sprite()
		{
			dispose();
		}

		bool Sprite::create(unsigned int vertexCount, float* colorBufferData)
		{
			int uvBufferSize = sizeof(float) * vertexCount * UV_COMPONENTS;

			_uvBufferData = generateUVBufferData(0, 0);
			_uvBufferID = _renderer->generateVertexBuffer(_uvBufferData, uvBufferSize);

			return Shape::create(vertexCount);
		}

		float* Sprite::generateVertexBufferData() const
		{
			float valueX = _frameWidth * 0.5f;
			float valueY = _frameHeight * 0.5f;

			float* vertexBufferData = new float[RECTANGLE_VERTICES * VERTEX_COMPONENTS]
			{
				-valueX, valueY, 0.0f,
				valueX, valueY, 0.0f,
				-valueX, -valueY, 0.0f,
				valueX, -valueY, 0.0f
			};

			return vertexBufferData;
		}

		float* Sprite::generateUVBufferData(float x, float y) const
		{
			float minU = x / _material->getTextureWidth();
			float maxU = (x + _frameWidth) / _material->getTextureWidth();
			float minV = 1.0f - (y + _frameHeight) / _material->getTextureHeight();
			float maxV = 1.0f - y / _material->getTextureHeight();

			float* uvBufferData = new float[RECTANGLE_VERTICES * UV_COMPONENTS]
			{
				minU, maxV,
				maxU, maxV,
				minU, minV,
				maxU, minV
			};

			return uvBufferData;
		}

		void Sprite::setAnimationFrame(unsigned int frameID)
		{
			_frameID = frameID;

			int uvBufferSize = sizeof(float) * RECTANGLE_VERTICES * UV_COMPONENTS;
			float x = (frameID % _columns) * _frameWidth;
			float y = (frameID / _rows) * _frameHeight;

			_uvBufferData = generateUVBufferData(x, y);
			_uvBufferID = _renderer->generateVertexBuffer(_uvBufferData, uvBufferSize);
		}

		void Sprite::setFramesInfo(unsigned int rows, unsigned int columns, float frameWidth, float frameHeight)
		{
			_rows = rows;
			_columns = columns;
			_frameWidth = frameWidth;
			_frameHeight = frameHeight;
		}

		void Sprite::dispose()
		{
			Shape::dispose();

			if (_uvBufferID != (unsigned int)-1)
			{
				_renderer->destroyBuffer(_uvBufferID);
				delete[] _uvBufferData;
				_uvBufferData = NULL;
				_uvBufferID = -1;
			}
		}

		void Sprite::draw() const
		{
			Shape::draw();

			_renderer->enableBlend();

			_renderer->enableAttribute(0);
			_renderer->enableAttribute(1);
			_renderer->bindBuffer(0, VERTEX_COMPONENTS, _vertexBufferID);
			_renderer->bindBuffer(1, UV_COMPONENTS, _uvBufferID);
			_renderer->drawBuffer(PrimitiveType::TRIANGLE_STRIP, RECTANGLE_VERTICES);
			_renderer->disableAttribute(0);
			_renderer->disableAttribute(1);

			_renderer->disableBlend();
		}
	}
}