#include "ModelMesh.h"
#include "Renderer.h"

namespace gn
{
	ModelMesh::ModelMesh(Renderer* renderer, Material* material, 
	std::vector<ModelMeshVertex> vertices, std::vector<unsigned int> indexes) :
	Mesh(renderer, material), _vertices(vertices), _indexes(indexes)
	{
		create(vertices.size());
	}

	ModelMesh::~ModelMesh()
	{
		//dispose();
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

		for (int i = 0; i < _vertices.size(); i += VERTEX_COMPONENTS)
		{
			vertexBufferData[i] = _vertices[i].position.x;
			vertexBufferData[i + 1] = _vertices[i].position.y;
			vertexBufferData[i + 2] = _vertices[i].position.z;
		}

		return vertexBufferData;
	}

	float* ModelMesh::generateUVBufferData() const
	{
		float* uvBufferData = new float[_vertices.size() * UV_COMPONENTS];

		for (int i = 0; i < _vertices.size(); i += UV_COMPONENTS)
		{
			uvBufferData[i] = _vertices[i].uvCoordinates.x;
			uvBufferData[i + 1] = _vertices[i].uvCoordinates.y;
		}

		return uvBufferData;
	}

	// Enhance this nonsense.
	std::vector<unsigned int> ModelMesh::generateIndexBufferData() const
	{
		std::vector<unsigned int> indexBufferData(_indexes);
		
		return indexBufferData;
	}

	void ModelMesh::dispose()
	{
		Mesh::dispose();

		if (_uvBufferID != (unsigned int)-1)
		{
			_renderer->destroyBuffer(_uvBufferID);
			_uvBufferID = -1;
		}
	}

	void ModelMesh::draw() const
	{
		Shape::draw();

		_renderer->enableAttribute(0);
		_renderer->bindBuffer(0, VERTEX_COMPONENTS, _vertexBufferID);
		_renderer->bindIndexBuffer(_indexBufferID);
		_renderer->drawIndexedBuffer(PrimitiveType::TRIANGLE, _indexBufferData.size());
		_renderer->disableAttribute(0);
	}
}