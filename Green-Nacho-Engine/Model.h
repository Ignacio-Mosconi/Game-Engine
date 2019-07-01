#pragma once

#include <string>
#include <vector>

#include "Entity.h"

#include "Exports.h"

enum aiTextureType;

struct aiNode;
struct aiScene;
struct aiMesh;
struct aiScene;
struct aiMaterial;

namespace gn
{
	class Texture;

	namespace legacy
	{
		struct ModelMeshVertex;
		class ModelMesh;

		class ENGINE_DECL_SPEC Model : public Entity
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
}