#pragma once

#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Entity.h"

#include "Exports.h"

namespace gn
{
	struct ModelMeshVertex;
	class ModelMesh;
	class Texture;

	class ENGINE_API Model : public Entity
	{
	private:
		std::vector<ModelMesh*> _modelMeshes;
		std::vector<Texture*> _textures;

		std::string _modelDirectory;

		void loadModel(const std::string& modelPath, bool hasTextures = false);
		void processNode(aiNode* node, const aiScene* scene, bool hasTextures = false);
		ModelMesh* generateMesh(aiMesh* mesh, const aiScene* scene, bool hasTextures = false);

		std::vector<Texture*> loadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName);

	public:
		Model(Renderer* _renderer, const char* modelPath, bool hasTextures = false);
		~Model();

		void dispose();

		void draw() const;
	};
}