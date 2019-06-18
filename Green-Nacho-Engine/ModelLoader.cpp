#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "ModelLoader.h"
#include "GameObject.h"
#include "Material.h"
#include "MeshRenderer.h"

namespace gn
{
	GameObject* ModelLoader::loadModel(GameObject* parent, const std::string& modelPath, const std::string& texturesPath)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs);
		
		std::cout << "Loading the 3D model... " << std::endl;

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "Error loading the model: " << importer.GetErrorString() << std::endl;
			return NULL;
		}

		GameObject* modelRoot = new GameObject(parent->getRenderer(), parent);

		processNode(modelRoot, scene->mRootNode, scene, texturesPath);

		return modelRoot;
	}

	void ModelLoader::processNode(GameObject* parent, aiNode* node, const aiScene* scene, const std::string& texturesPath)
	{
		for (int i = 0; i < (int)node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			GameObject* child = generateMesh(parent, mesh, scene, texturesPath);
		}

		for (int i = 0; i < (int)node->mNumChildren; i++)
			processNode(parent, node->mChildren[i], scene, texturesPath);
	}

	GameObject* ModelLoader::generateMesh(GameObject* parent, aiMesh* mesh, const aiScene* scene, const std::string& texturesPath)
	{
		GameObject* gameObject = new GameObject(parent->getRenderer(), parent);

		std::vector<MeshVertex> vertices;
		std::vector<unsigned int> indices;

		for (int i = 0; i < (int)mesh->mNumVertices; i++)
		{
			MeshVertex vertex;
			aiVector3D aiMeshVertex = mesh->mVertices[i];
			aiVector3D aiMeshNormal = mesh->mNormals[i];
			aiVector3D aiTextCoord(0.0f, 0.0f, 0.0f);

			if (mesh->mTextureCoords[0])
				aiTextCoord = mesh->mTextureCoords[0][i];

			vertex.position = glm::vec3(aiMeshVertex.x, aiMeshVertex.y, aiMeshVertex.z);
			vertex.normal = glm::vec3(aiMeshNormal.x, aiMeshNormal.y, aiMeshNormal.z);
			vertex.uvCoords = glm::vec2(aiTextCoord.x, aiTextCoord.y);

			vertices.push_back(vertex);
		}

		for (int i = 0; i < (int)mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];

			for (int j = 0; j < (int)face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		std::vector<Texture*> diffuseMaps;

		if (mesh->mMaterialIndex >= 0 && texturesPath != "")
		{
			aiMaterial* aiMat = scene->mMaterials[mesh->mMaterialIndex];
			diffuseMaps = loadMaterialTextures(aiMat, aiTextureType_DIFFUSE, texturesPath);
		}

		MeshRenderer* meshRenderer = (MeshRenderer*)gameObject->addComponent(ComponentID::MeshRenderer);
		meshRenderer->createMesh(gameObject->getRenderer(), vertices, indices, diffuseMaps);

		return gameObject;
	}

	std::vector<Texture*> ModelLoader::loadMaterialTextures(aiMaterial* material, aiTextureType type, const std::string& texturesPath)
	{
		std::vector<Texture*> textures;

		for (int i = 0; i < (int)material->GetTextureCount(type); i++)
		{
			Texture* texture;
			aiString string;
			std::string imagePath;

			material->GetTexture(type, i, &string);
			imagePath = texturesPath + "\\" + string.C_Str();
			texture = Texture::generateTexture(imagePath);

			textures.push_back(texture);
		}

		return textures;
	}
}