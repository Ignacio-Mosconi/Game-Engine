#pragma once

#include <string>
#include <vector>
#include <glm/vec3.hpp>
#include "Core/Exports.h"

enum aiTextureType;

struct aiNode;
struct aiScene;
struct aiMesh;
struct aiScene;
struct aiMaterial;
struct aiTexture;

namespace gn
{
	class GameObject;
	class MeshRenderer;
	class Material;
	class Texture;

	class ENGINE_DECL_SPEC ModelLoader
	{
	private:
		static void processNode(GameObject* parent, aiNode* node, const aiScene* scene, glm::vec3& mins, glm::vec3& maxs,
								const std::string& texturesPath = "");
		static GameObject* generateMesh(GameObject* parent, aiMesh* mesh, const aiScene* scene, glm::vec3& mins, glm::vec3& maxs,
										const std::string& texturesPath = "");
		static std::vector<Texture*> loadMaterialTextures(aiMaterial* material, aiTextureType type, const std::string& texturesPath);
		static std::vector<Texture*> loadMaterialTextures(aiTexture** textures);

	public:
		static GameObject* loadModel(GameObject* parent, const std::string& modelPath, const std::string& texturesPath = "");
		static GameObject* loadTerrain(GameObject* parent, const std::string& heightmapPath, glm::vec3 scale);
	};
}