#include "Scene Graph/MeshRenderer.h"
#include "Core/Renderer.h"
#include "Core/Material.h"
#include "Scene Graph/GameObject.h"

namespace gn
{
	MeshRenderer::MeshRenderer(GameObject* gameObject) : Component(ComponentID::MESH_RENDERER, gameObject),
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
	
	float* MeshRenderer::generateCustomBufferData(std::vector<float*> values, int components)
	{
		float* bufferData = new float[values.size() * components];

		for (int i = 0, j = 0; i < (int)values.size(); i++, j += components)
		{
			for (int k = 0; k < components; k++)
				bufferData[j + k] = values[i][k];
		}

		return bufferData;
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

		_renderer = _gameObject->getRenderer();

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


		for (int i = 2; i < _customBufferDataByAttribute.size(); i++)
		{
			CustomBufferData customBufferData = _customBufferDataByAttribute.at(i);

			if (customBufferData.bufferData)
			{
				_renderer->destroyBuffer(customBufferData.bufferID);
				delete[] customBufferData.bufferData;
				_customBufferDataByAttribute.erase(i);
			}
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

		for (int i = 2; i < _customBufferDataByAttribute.size() + 2; i++)
		{
			CustomBufferData customBufferData = _customBufferDataByAttribute.at(i);
			
			if (customBufferData.bufferData)
			{
				_renderer->enableAttribute(i);
				_renderer->bindBuffer(i, customBufferData.components, customBufferData.bufferID);
			}
		}

		_renderer->bindIndexBuffer(_indexBufferID);
		_renderer->drawIndexedBuffer(PrimitiveType::TRIANGLE, (unsigned int)_indexBufferData.size());
		
		_renderer->disableAttribute(0);
		_renderer->disableAttribute(1);

		for (int i = 2; i < _customBufferDataByAttribute.size() + 2; i++)
		{
			CustomBufferData customBufferData = _customBufferDataByAttribute.at(i);

			if (customBufferData.bufferData)
				_renderer->disableAttribute(i);
		}
	}

	void MeshRenderer::createMesh(std::vector<MeshVertex> vertices, std::vector<unsigned int> indices,
									std::vector<Texture*> diffuseTextures,
									const std::string& vertexShaderPath, 
									const std::string& pixelShaderPath)
	{
		std::vector<glm::vec3> positions;
		std::vector<glm::vec2> uvCoords;

		for (int i = 0; i < (int)vertices.size(); i++)
		{
			positions.push_back(vertices[i].position);
			uvCoords.push_back(vertices[i].uvCoord);
		}

		_vertexCount = (unsigned int)vertices.size();
		
		_vertexBufferData = generateVertexBufferData(positions);
		_uvBufferData = generateUVBufferData(uvCoords);
		
		setIndexBufferData(indices);

		if (diffuseTextures.size() > 0)
		{
			_material = Material::generateMaterial(vertexShaderPath, pixelShaderPath);
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
	
	void MeshRenderer::addCustomBuffer(const int& attribute, std::vector<float*> values, const int& components)
	{
		if (_customBufferDataByAttribute[attribute].bufferData)
		{
			std::cout << "Warning: Attempted to overwrite the custom buffer with attribute ID " << attribute << std::endl;
			return;
		}
		
		CustomBufferData customBufferData;
		int size = sizeof(float) * values.size() * components;
		
		customBufferData.components = components;
		customBufferData.bufferData = generateCustomBufferData(values, components);
		customBufferData.bufferID = _renderer->generateVertexBuffer(customBufferData.bufferData, size);

		_customBufferDataByAttribute[attribute] = customBufferData;
	}
}