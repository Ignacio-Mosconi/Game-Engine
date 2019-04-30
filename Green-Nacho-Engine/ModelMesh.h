#pragma once

#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "Mesh.h"
#include "Exports.h"

namespace gn
{
	struct ModelMeshVertex
	{
		glm::vec3 position;
		glm::vec2 uvCoordinates;
		bool operator<(const ModelMeshVertex that) const 
		{
			return memcmp((void*)this, (void*)&that, sizeof(ModelMeshVertex)) > 0;
		}
	};

	class ENGINE_API ModelMesh : public Mesh
	{
	private:
		std::vector<ModelMeshVertex> _vertices;
		std::vector<unsigned int> _indexes;

	protected:
		float* _uvBufferData;

		unsigned int _uvBufferID;

		bool create(unsigned int vertexCount, float* colorBufferData = NULL) override;

		float* generateVertexBufferData() const override;
		float* generateUVBufferData() const;
		std::vector<unsigned int> generateIndexBufferData() const override;

	public:
		ModelMesh(Renderer* renderer, Material* material, std::vector<ModelMeshVertex> vertices, std::vector<unsigned int> indexes);
		~ModelMesh();

		void dispose() override;

		void draw() const override;
	};
}