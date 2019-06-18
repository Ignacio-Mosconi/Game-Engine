#include "MeshRenderer.h"
#include "Renderer.h"
#include "Material.h"

namespace gn
{
	MeshRenderer::MeshRenderer() : Component(ComponentID::MeshRenderer),
		_renderer(NULL), _diffuseTextures(NULL), _material(NULL),
		_vertexBufferData(NULL), _uvBufferData(NULL), _indexBufferData(NULL),
		_vertexBufferID(-1), _uvBufferID(-1), _indexBufferID(-1)
	{

	}

	MeshRenderer::~MeshRenderer()
	{

	}

	float* MeshRenderer::generateVertexBufferData(std::vector<glm::vec3> positions)
	{
		float* vertexBufferData = new float[positions.size() * VERTEX_COMPONENTS];

		for (int i = 0, j = 0; i < (int)positions.size(); i++, j += VERTEX_COMPONENTS)
		{
			vertexBufferData[j] = positions[i].x;
			vertexBufferData[j + 1] = positions[i].y;
			vertexBufferData[j + 2] = positions[i].z;
		}

		return vertexBufferData;
	}

	float* MeshRenderer::generateUVBufferData(std::vector<glm::vec2> uvCoords)
	{
		float* uvBufferData = new float[uvCoords.size() * UV_COMPONENTS];

		for (int i = 0, j = 0; i < (int)uvCoords.size(); i++, j += UV_COMPONENTS)
		{
			uvBufferData[j] = uvCoords[i].x;
			uvBufferData[j + 1] = uvCoords[i].y;
		}

		return uvBufferData;
	}

	void MeshRenderer::setIndexBufferData(std::vector<unsigned int> indices)
	{
		_indexBufferData = indices;
	}

	void MeshRenderer::start()
	{
		int vertexBufferSize = sizeof(float) * _vertexCount * VERTEX_COMPONENTS;
		int uvBufferSize = sizeof(float) * _vertexCount * UV_COMPONENTS;
		int indexBufferSize = sizeof(unsigned int) * (int)_indexBufferData.size();

		_vertexBufferID = _renderer->generateVertexBuffer(_vertexBufferData, vertexBufferSize);
		_uvBufferID = _renderer->generateVertexBuffer(_uvBufferData, uvBufferSize);
		_indexBufferID = _renderer->generateIndexBuffer(_indexBufferData, indexBufferSize);
	}

	void MeshRenderer::stop()
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
			
		if (_indexBufferID != -1)
		{
			_renderer->destroyBuffer(_indexBufferID);
			_indexBufferData.clear();
			_indexBufferID = -1;
		}

		if (_renderer)
			disposeMesh();
	}

	void MeshRenderer::draw() const
	{
		_material->bind();
		_material->setMatrixProperty("MVP", _renderer->getMVP());
		_material->bindTexture();

		_renderer->enableAttribute(0);
		_renderer->enableAttribute(1);
		_renderer->bindBuffer(0, VERTEX_COMPONENTS, _vertexBufferID);
		_renderer->bindBuffer(1, UV_COMPONENTS, _uvBufferID);
		_renderer->bindIndexBuffer(_indexBufferID);
		_renderer->drawIndexedBuffer(PrimitiveType::TRIANGLE, (unsigned int)_indexBufferData.size());
		_renderer->disableAttribute(0);
		_renderer->disableAttribute(1);
	}

	void MeshRenderer::createMesh(Renderer* renderer, std::vector<MeshVertex> vertices, std::vector<unsigned int> indices,
									std::vector<Texture*> diffuseTextures)
	{
		std::vector<glm::vec3> positions;
		std::vector<glm::vec2> uvCoords;

		for (int i = 0; i < (int)vertices.size(); i++)
		{
			positions.push_back(vertices[i].position);
			uvCoords.push_back(vertices[i].uvCoords);
		}

		_vertexCount = (unsigned int)vertices.size();
		
		_vertexBufferData = generateVertexBufferData(positions);
		_uvBufferData = generateUVBufferData(uvCoords);
		
		setIndexBufferData(indices);

		_renderer = renderer;

		if (diffuseTextures.size() > 0)
		{
			_material = Material::generateMaterial(MODEL_TEX_VERTEX_SHADER_PATH, MODEL_TEX_PIXEL_SHADER_PATH);
			_diffuseTextures = diffuseTextures;
			_material->setTexture(diffuseTextures[0], "textureDiffuse");
		}
		else
			_material = Material::generateMaterial(SIMPLE_VERTEX_SHADER_PATH, SIMPLE_PIXEL_SHADER_PATH);
	}

	void MeshRenderer::disposeMesh()
	{
		Material::destroyMaterial(_material);
		_renderer = NULL;
	}
}