#include "ModelMesh.h"
#include "Renderer.h"
#include "Material.h"

namespace gn
{
	ModelMesh::ModelMesh(Renderer* renderer, Material* material, 
	std::vector<ModelMeshVertex>& vertices, std::vector<unsigned int>& indexes) :
	Mesh(renderer, material), _vertices(vertices), _indexes(indexes)
	{
		create((unsigned int)vertices.size());
	}

	ModelMesh::~ModelMesh()
	{
		dispose();
	}
	
	bool ModelMesh::create(unsigned int vertexCount, float* colorBufferData)
	{
		_uvBufferData = generateUVBufferData();	

		int uvBufferSize = sizeof(float) * vertexCount * UV_COMPONENTS;

		_uvBufferID = _renderer->generateVertexBuffer(_uvBufferData, uvBufferSize);
		
		return (Mesh::create(vertexCount));
	}

	float* ModelMesh::generateVertexBufferData() const
	{
		float* vertexBufferData = new float[_vertices.size() * VERTEX_COMPONENTS];

		for (int i = 0, j = 0; i < (int)_vertices.size(); i++, j += VERTEX_COMPONENTS)
		{
			vertexBufferData[j] = _vertices[i].position.x;
			vertexBufferData[j + 1] = _vertices[i].position.y;
			vertexBufferData[j + 2] = _vertices[i].position.z;
		}

		return vertexBufferData;
	}

	float* ModelMesh::generateUVBufferData() const
	{
		float* uvBufferData = new float[_vertices.size() * UV_COMPONENTS];

		for (int i = 0, j = 0; i < (int)_vertices.size(); i++, j += UV_COMPONENTS)
		{
			uvBufferData[j] = _vertices[i].uvCoordinates.x;
			uvBufferData[j + 1] = _vertices[i].uvCoordinates.y;
		}

		return uvBufferData;
	}

	std::vector<unsigned int> ModelMesh::generateIndexBufferData() const
	{	
		return _indexes;
	}

	void ModelMesh::dispose()
	{
		Mesh::dispose();

		if (_uvBufferID != (unsigned int)-1)
		{
			_renderer->destroyBuffer(_uvBufferID);
			_uvBufferID = -1;
		}

		Material::destroyMaterial(_material);
	}

	void ModelMesh::draw() const
	{
		Shape::draw();

		_renderer->enableAttribute(0);
		_renderer->enableAttribute(1);
		_renderer->bindBuffer(0, VERTEX_COMPONENTS, _vertexBufferID);
		_renderer->bindBuffer(1, UV_COMPONENTS, _uvBufferID);
		_renderer->bindIndexBuffer(_indexBufferID);
		_renderer->drawIndexedBuffer(PrimitiveType::TRIANGLE, (unsigned int)_indexBufferData.size());
		_renderer->disableAttribute(0);
		_renderer->disableAttribute(1);
	}
}