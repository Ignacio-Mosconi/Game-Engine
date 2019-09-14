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
	class BoundingBox;
	class Material;
	class Texture;

	class ENGINE_DECL_SPEC ModelLoader
	{
	private:
		static void processNode(GameObject* parent, aiNode* node, const aiScene* scene, glm::vec3& mins, glm::vec3& maxs,
								const std::string& texturesPath = "");
		static GameObject* generateMesh(GameObject* parent, aiMesh* mesh, const aiScene* scene, glm::vec3& mins, glm::vec3& maxs,
										glm::vec3& localMins, glm::vec3& localMaxs, const std::string& texturesPath = "");
		static void addBoundingBox(GameObject* owner, glm::vec3 mins, glm::vec3 maxs);
		static std::vector<Texture*> loadMaterialTextures(aiMaterial* material, aiTextureType type, const std::string& texturesPath);
		static std::vector<Texture*> loadMaterialTextures(aiTexture** textures);

		static std::vector<unsigned int> generateTerrainIndices(int rows, int columns);

	public:
		static GameObject* loadModel(GameObject* parent, const std::string& modelPath, const std::string& texturesPath = "");
		static GameObject* loadTerrain(GameObject* parent, const std::string& heightmapPath, glm::vec3 scale, 
										const std::string& texturesPath = "");
		static GameObject* loadRandomTerrain(GameObject* parent, int rows, int columns, glm::vec3 scale, 
										const std::string& texturesPath = "");
	};
}