#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "ModelLoader.h"
#include "Core/Material.h"
#include "Scene Graph/GameObject.h"
#include "Scene Graph/BoundingBox.h"
#include "Scene Graph/MeshRenderer.h"
#include "Scene Graph/Terrain.h"
#include "Scene Graph/RandomHeightGenerator.h"

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

		glm::vec3 mins = glm::vec3(0.0f);
		glm::vec3 maxs = glm::vec3(0.0f);

		processNode(modelRoot, scene->mRootNode, scene, mins, maxs, texturesPath);

		glm::vec3 bbVertices[CUBE_VERTICES] =
		{
			glm::vec3(mins.x, mins.y, mins.z),
			glm::vec3(mins.x, maxs.y, mins.z),
			glm::vec3(mins.x, mins.y, maxs.z),
			glm::vec3(mins.x, maxs.y, maxs.z),
			glm::vec3(maxs.x, mins.y, mins.z),
			glm::vec3(maxs.x, maxs.y, mins.z),
			glm::vec3(maxs.x, mins.y, maxs.z),
			glm::vec3(maxs.x, maxs.y, maxs.z)
		};
		
		BoundingBox* bb = (BoundingBox*)modelRoot->addComponent(ComponentID::BOUNDING_BOX);
		bb->setVertices(bbVertices);

		return modelRoot;
	}

	GameObject* ModelLoader::loadTerrain(GameObject* parent, const std::string& heightmapPath, glm::vec3 scale, 
										const std::string& texturesPath)
	{
		GameObject* terrainObject = new GameObject(parent->getRenderer(), parent);

		int hmColumns, hmRows;
		unsigned char* heightmap = Texture::loadHeightmap(heightmapPath, hmColumns, hmRows);

		unsigned char* pixel = heightmap;
		
		std::vector<MeshVertex> vertices;
		std::vector<std::vector<int>> heights;

		std::vector<int> currentRowHeights;

		for (unsigned int row = 0; row < (unsigned int)hmRows; row++)
		{
			currentRowHeights.clear();

			for (unsigned int col = 0; col < (unsigned int)hmColumns; col++)
			{
				MeshVertex vertex;
				
				float posX = col * scale.x;
				float posY = (float)*pixel / MAX_BYTE_VALUE * scale.y;
				float posZ = row * scale.z;

				float u = (float)col / (float)hmColumns;
				float v = 1.0f - (float)row / (float)hmRows;
				
				vertex.position = glm::vec3(posX, posY, posZ);
				vertex.normal = glm::vec3 (0.0f);
				vertex.uvCoord = glm::vec2 (u, v);

				currentRowHeights.push_back((int)*pixel);
				vertices.push_back(vertex);
				pixel++;
			}
			
			heights.push_back(currentRowHeights);
		}

		std::vector<unsigned int> indices = generateTerrainIndices(hmRows, hmColumns);

		return terrainObject;
	}

	GameObject* ModelLoader::loadRandomTerrain(GameObject* parent, int rows, int columns, glm::vec3 scale, 
												const std::string& texturesPath)
	{
		RandomHeightGenerator::generateSeed();

		GameObject* terrainObject = new GameObject(parent->getRenderer(), parent);

		std::vector<MeshVertex> vertices;
		std::vector<std::vector<int>> heights;

		std::vector<int> currentRowHeights;

		for (unsigned int row = 0; row < (unsigned int)rows; row++)
		{
			currentRowHeights.clear();

			for (unsigned int col = 0; col < (unsigned int)columns; col++)
			{
				MeshVertex vertex;

				int randomHeight = RandomHeightGenerator::generateHeight(row, col);

				float posX = col * scale.x;
				float posY = (float)randomHeight / MAX_BYTE_VALUE * scale.y;
				float posZ = row * scale.z;

				float u = (float)col / (float)columns;
				float v = 1.0f - (float)row / (float)rows;

				vertex.position = glm::vec3(posX, posY, posZ);
				vertex.normal = glm::vec3(0.0f);
				vertex.uvCoord = glm::vec2(u, v);

				currentRowHeights.push_back(randomHeight);
				vertices.push_back(vertex);
			}

			heights.push_back(currentRowHeights);
		}

		std::vector<unsigned int> indices = generateTerrainIndices(rows, columns);

		std::vector<Texture*> diffuseMaps;

		if (texturesPath != "")
		{
			Texture* diffuseMap = Texture::generateTexture(texturesPath);
			diffuseMaps.push_back(diffuseMap);
		}

		Terrain* terrain = (Terrain*)terrainObject->addComponent(ComponentID::TERRAIN);
		terrain->createHeightField(heights, rows, columns, scale);

		MeshRenderer* meshRenderer = (MeshRenderer*)terrainObject->addComponent(ComponentID::MESH_RENDERER);
		meshRenderer->createMesh(vertices, indices, diffuseMaps);

		return terrainObject;
	}

	void ModelLoader::processNode(GameObject* parent, aiNode* node, const aiScene* scene, glm::vec3& mins, glm::vec3& maxs, 
								const std::string& texturesPath)
	{
		for (int i = 0; i < (int)node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			GameObject* child = generateMesh(parent, mesh, scene, mins, maxs, texturesPath);
		}

		for (int i = 0; i < (int)node->mNumChildren; i++)
			processNode(parent, node->mChildren[i], scene, mins, maxs, texturesPath);
	}

	GameObject* ModelLoader::generateMesh(GameObject* parent, aiMesh* mesh, const aiScene* scene, glm::vec3& mins, glm::vec3& maxs,
											const std::string& texturesPath)
	{
		GameObject* gameObject = new GameObject(parent->getRenderer(), parent);

		std::vector<MeshVertex> vertices;
		std::vector<unsigned int> indices;

		for (int i = 0; i < (int)mesh->mNumVertices; i++)
		{
			MeshVertex vertex;
			aiVector3D aiVertex = mesh->mVertices[i];
			aiVector3D aiNormal(0.0f, 0.0f, 0.0f);
			aiVector3D aiTextCoord(0.0f, 0.0f, 0.0f);

			if (mesh->mNormals)
				aiNormal = mesh->mNormals[i];

			if (mesh->mTextureCoords[0])
				aiTextCoord = mesh->mTextureCoords[0][i];

			vertex.position = glm::vec3(aiVertex.x, aiVertex.y, aiVertex.z);
			vertex.normal = glm::vec3(aiNormal.x, aiNormal.y, aiNormal.z);
			vertex.uvCoord = glm::vec2(aiTextCoord.x, aiTextCoord.y);

			if (vertex.position.x < mins.x)
				mins.x = vertex.position.x;
			if (vertex.position.x > maxs.x)
				maxs.x = vertex.position.x;			
			if (vertex.position.y < mins.y)
				mins.y = vertex.position.y;
			if (vertex.position.y > maxs.y)
				maxs.y = vertex.position.y;
			if (vertex.position.z < mins.z)
				mins.z = vertex.position.z;
			if (vertex.position.z > maxs.z)
				maxs.z = vertex.position.z;

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
			diffuseMaps = (scene->HasTextures()) ? loadMaterialTextures(scene->mTextures) :
													loadMaterialTextures(aiMat, aiTextureType_DIFFUSE, texturesPath);
		}

		MeshRenderer* meshRenderer = (MeshRenderer*)gameObject->addComponent(ComponentID::MESH_RENDERER);
		meshRenderer->createMesh(vertices, indices, diffuseMaps);

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

	std::vector<Texture*> ModelLoader::loadMaterialTextures(aiTexture** aiTextures)
	{
		std::vector<Texture*> textures;
		
		Texture* texture;
		unsigned char* imageData = (unsigned char*)aiTextures[0]->pcData;

		texture = Texture::generateTexture(imageData);
		textures.push_back(texture);

		return textures;
	}

	std::vector<unsigned int> ModelLoader::generateTerrainIndices(int rows, int columns)
	{
		std::vector<unsigned int> indices;

		unsigned int start = 0;
		unsigned int gridRows = rows - 1;
		unsigned int gridColumns = columns - 1;

		for (unsigned int row = 0; row < gridRows; row++)
		{
			for (unsigned int col = 0; col < gridColumns; col++)
			{
				start = row * columns + col;

				indices.push_back(start);
				indices.push_back(start + 1);
				indices.push_back(start + columns);

				indices.push_back(start + columns);
				indices.push_back(start + columns + 1);
				indices.push_back(start + 1);
			}
		}

		return indices;
	}
}