#pragma once

#include <string>
#include "Exports.h"

enum aiTextureType;

struct aiNode;
struct aiScene;
struct aiMesh;
struct aiScene;
struct aiMaterial;

namespace gn
{
	class GameObject;
	class MeshRenderer;
	class Material;
	class Texture;

	static class ENGINE_API ModelLoader
	{
	private:
		static void processNode(GameObject* parent, aiNode* node, const aiScene* scene, const std::string& texturesPath = NULL);
		static GameObject* generateMesh(GameObject* parent, aiMesh* mesh, const aiScene* scene, const std::string& texturesPath = NULL);

	public:
		static GameObject* loadModel(GameObject* parent, const std::string& modelPath, const std::string& texturesPath = NULL);
	};
}