#pragma once

#include <string>
#include <vector>
#include <map>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Entity.h"

#include "Exports.h"

namespace gn
{
	struct ModelMeshVertex;
	class ModelMesh;

	class ENGINE_API Model : public Entity
	{
	private:
		std::vector<ModelMesh> _modelMeshes;

		void loadModel(const std::string& modelPath);
		void processNode(aiNode* node, const aiScene* scene);
		ModelMesh generateMesh(aiMesh* mesh, const aiScene* scene);

		//bool getSimilarVertex(ModelMeshVertex& vertex, std::map<ModelMeshVertex, unsigned int>& vertexMap, 
		//					unsigned int& resultingIndex) const;

	public:
		Model(Renderer* _renderer, const char* modelPath);
		~Model();

		void dispose();

		void draw() const;
	};
}