#include "Scene Graph/SpriteRenderer.h"
#include "Core/Renderer.h"
#include "Core/Material.h"

namespace gn
{
	SpriteRenderer::SpriteRenderer(): Component(ComponentID::SpriteRenderer),
		_renderer(NULL), _texture(NULL), _material(NULL),
		_vertexBufferData(NULL), _uvBufferData(NULL),
		_vertexBufferID(-1), _uvBufferID(-1),
		_frameID(0), _rows(1), _columns(1), _frameWidth(0), _frameHeight(0)
	{

	}
	
	SpriteRenderer::~SpriteRenderer()
	{

	}

	float* SpriteRenderer::generateVertexBufferData() const
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

	float* SpriteRenderer::generateUVBufferData(float x, float y) const
	{
		float minU = x / _texture->getWidth();
		float maxU = (x + _frameWidth) / _texture->getWidth();
		float minV = 1.0f - (y + _frameHeight) / _texture->getHeight();
		float maxV = 1.0f - y / _texture->getHeight();

		float* uvBufferData = new float[RECTANGLE_VERTICES * UV_COMPONENTS]
		{
			minU, maxV,
			maxU, maxV,
			minU, minV,
			maxU, minV
		};

		return uvBufferData;
	}

	void SpriteRenderer::start()
	{
		int vertexBufferSize = sizeof(float) * RECTANGLE_VERTICES * VERTEX_COMPONENTS;
		int uvBufferSize = sizeof(float) * RECTANGLE_VERTICES * UV_COMPONENTS;

		_vertexBufferData = generateVertexBufferData();
		_uvBufferData = generateUVBufferData(0.0f, 0.0f);

		_vertexBufferID = _renderer->generateVertexBuffer(_vertexBufferData, vertexBufferSize);
		_uvBufferID = _renderer->generateVertexBuffer(_uvBufferData, uvBufferSize);
	}

	void SpriteRenderer::stop()
	{
		if (_vertexBufferID != -1)
		{
			_renderer->destroyBuffer(_vertexBufferID);
			delete[] _vertexBufferData;
			_vertexBufferData = NULL;
			_vertexBufferID = -1;
		}		
		
		if (_uvBufferID != -1)
		{
			_renderer->destroyBuffer(_uvBufferID);
			delete[] _uvBufferData;
			_uvBufferData = NULL;
			_uvBufferID = -1;
		}

		if (_renderer)
			disposeSprite();
	}

	void SpriteRenderer::draw() const
	{
		_material->bind();
		_material->setMatrixProperty("MVP", _renderer->getMVP());
		_material->bindTexture();

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

	void SpriteRenderer::createSprite(Renderer* renderer, const std::string& spritePath, 
										unsigned int rows, unsigned int columns)
	{
		_material = Material::generateMaterial(TEXTURE_VERTEX_SHADER_PATH, TEXTURE_PIXEL_SHADER_PATH);
		_texture = Texture::generateTextureBMP(spritePath);
		_material->setTexture(_texture, "textureSampler");
		
		_renderer = renderer;
		_rows = rows;
		_columns = columns;
		_frameWidth = (float)(_texture->getWidth() / _columns);
		_frameHeight = (float)(_texture->getHeight() / _rows);
	}	
	
	void SpriteRenderer::disposeSprite()
	{
		Material::destroyMaterial(_material);
		Texture::destroyTexture(_texture);

		_renderer = NULL;
	}	
	
	void SpriteRenderer::setFramesInfo(unsigned int rows, unsigned int columns, float frameWidth, float frameHeight)
	{
		_rows = rows;
		_columns = columns;
		_frameWidth = frameWidth;
		_frameHeight = frameHeight;
	}
}