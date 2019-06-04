#include "SpriteRenderer.h"
#include "Renderer.h"
#include "Material.h"

namespace gn
{
	SpriteRenderer::SpriteRenderer(Renderer* renderer, const std::string& spritePath, 
		unsigned int rows, unsigned int columns) : Component("SpriteRenderer"),
		_renderer(renderer),
		_texture(Texture::generateTexture(spritePath)),
		_material(Material::generateMaterial(TEXTURE_VERTEX_SHADER_PATH, TEXTURE_PIXEL_SHADER_PATH)),
		_vertexBufferData(NULL), _uvBufferData(NULL),
		_vertexBufferID(-1), _uvBufferID(-1),
		_frameID(0), _rows(rows), _columns(columns), _frameWidth(0), _frameHeight(0)
	{
		_material->setTexture(_texture, "textureSampler");
		_frameWidth = _texture->getWidth() / columns;
		_frameHeight= _texture->getHeight() / rows;
	}
	
	SpriteRenderer::~SpriteRenderer()
	{
		Texture::destroyTexture(_texture);
		Material::destroyMaterial(_material);
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

	}

	void SpriteRenderer::update()
	{

	}

	void SpriteRenderer::draw(glm::mat4 modelMatrix) const
	{
		_renderer->setModelMatrix(modelMatrix);

		_material->bind();
		_material->setMatrixProperty("MVP", _renderer->getMVP());
		_material->bindTexture();
	}
}