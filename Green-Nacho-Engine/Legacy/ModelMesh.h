#pragma once

#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "Legacy/Mesh.h"
#include "Core/Exports.h"

namespace gn
{
	namespace legacy
	{
		struct ModelMeshVertex
		{
			glm::vec3 position;
			glm::vec2 normal;
			glm::vec2 uvCoordinates;
		};

		class ENGINE_DECL_SPEC ModelMesh : public Mesh
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
			ModelMesh(Renderer* renderer, Material* material, std::vector<ModelMeshVertex>& vertices,
				std::vector<unsigned int>& indexes);
			~ModelMesh();

			void dispose() override;

			void draw() const override;
		};
	}
}