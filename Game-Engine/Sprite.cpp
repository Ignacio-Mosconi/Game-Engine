#include "Sprite.h"
#include "Sprite.h"
#include "Material.h"
#include "Renderer.h"

namespace gn
{
	Sprite::Sprite(Renderer* renderer, Material* material) : Shape(renderer, material, 4),
	_uvBufferData(NULL),
	_uvBufferID(-1),
	_frameID(0), _rows(0), _columns(0), _frameWidth(0), _frameHeight(0)
	{
		std::cout << "Sprite::Sprite()" << std::endl;
	}

	Sprite::~Sprite()
	{
		std::cout << "Sprite::~Sprite()" << std::endl;
	}

	bool Sprite::create(unsigned int vertexComponents, float* colorBufferData, float width, float height, float depth)
	{
		int uvBufferSize = sizeof(float) * _vertexCount * 2;

		_uvBufferData = setVerticesUV(0, 0);
		_uvBufferID = _renderer->generateVertexBuffer(_uvBufferData, uvBufferSize);

		return Shape::create(vertexComponents, NULL, width, height, depth);
	}

	float* Sprite::setVertices(unsigned int vertexComponents, float width, float height, float depth) const
	{
		float valueX = width * 0.5f;
		float valueY = height * 0.5f;

		float* vertexBufferData = new float[_vertexCount * vertexComponents]
		{
			-valueX, valueY, depth,
			valueX, valueY, depth,
			-valueX, -valueY, depth,
			valueX, -valueY, depth
		};

		return vertexBufferData;
	}

	float* Sprite::setVerticesUV(unsigned int x, unsigned int y) const
	{
		float minU = (float)x / (float)_material->getTextureWidth();
		float maxU = (float)(x + _frameWidth) / (float)_material->getTextureWidth();
		float minV = 1.0f - (float)(y + _frameHeight) / (float)_material->getTextureHeight();
		float maxV = 1.0f - (float)y / (float)_material->getTextureHeight();

		float* uvBufferData = new float[_vertexCount * 2]
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
	
		int uvBufferSize = sizeof(float) * _vertexCount * 2;
		unsigned int x = (frameID % _columns) * _frameWidth;
		unsigned int y = (frameID / _rows) * _frameHeight;
	
		_uvBufferData = setVerticesUV(x, y);
		_uvBufferID = _renderer->generateVertexBuffer(_uvBufferData, uvBufferSize);
	}

	void Sprite::setFramesInfo(unsigned int rows, unsigned int columns, unsigned int frameWidth, unsigned int frameHeight)
	{
		_rows = rows;
		_columns = columns;
		_frameWidth = frameWidth;
		_frameHeight = frameHeight;
	}

	void Sprite::dispose()
	{
		Shape::dispose();

		if (_uvBufferID != -1)
		{
			_renderer->destroyVertexBuffer(_uvBufferID);
			delete _uvBufferData;
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
		_renderer->bindBuffer(0, 3, _vertexBufferID);
		_renderer->bindBuffer(1, 2, _uvBufferID);
		_renderer->drawBuffer(TRIANGLE_STRIP, _vertexCount);
		_renderer->disableAttribute(0);
		_renderer->disableAttribute(1);

		_renderer->disableBlend();
	}
}