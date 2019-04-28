#include "ModelMesh.h"

namespace gn
{
	ModelMesh::ModelMesh(Renderer* renderer, std::vector<ModelMeshVertex> vertices, std::vector<unsigned short> indexes) :
	Entity(renderer), _vertices(vertices), _indexes(indexes)
	{
		create();
	}

	ModelMesh::~ModelMesh()
	{

	}
	
	void ModelMesh::create()
	{
		float* vertexBufferData = new float[_vertices.size() * VERTEX_COMPONENTS];
		float* uvBufferData = new float[_vertices.size() * UV_COMPONENTS];

		for (int i = 0; i < _vertices.size(); i += VERTEX_COMPONENTS)
		{
			vertexBufferData[i] = _vertices[i].position.x;
			vertexBufferData[i + 1] = _vertices[i].position.y;
			vertexBufferData[i + 2] = _vertices[i].position.z;			
		}		
		
		for (int i = 0; i < _vertices.size(); i += UV_COMPONENTS)
		{
			uvBufferData[i] = _vertices[i].position.x;
			uvBufferData[i + 1] = _vertices[i].position.y;
		}

		int vertexBufferSize = sizeof(float) * _vertices.size() * VERTEX_COMPONENTS;
		int uvBufferSize = sizeof(float) * _vertices.size() * UV_COMPONENTS;
		int indexBufferSize = sizeof(unsigned short) * _indexes.size();

		_renderer->generateVertexBuffer(vertexBufferData, vertexBufferSize);
		_renderer->generateVertexBuffer(uvBufferData, uvBufferSize);
		_renderer->generateIndexBuffer(_indexes, vertexBufferSize);
	}

	void ModelMesh::draw() const
	{
		_renderer->loadIdentityMatrix();
		_renderer->setModelMatrix(_modelMatrix);

		//if (_material)
		//{
		//	_material->bind();
		//	_material->setMatrixProperty("MVP", _renderer->getMVP());
		//	_material->bindTexture();
		//}
	}
}