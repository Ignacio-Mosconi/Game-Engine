#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Legacy/Model.h"
#include "Legacy/ModelMesh.h"
#include "Core/Material.h"

namespace gn
{
	namespace legacy
	{
		Model::Model(Renderer* renderer, const char* modelPath, bool hasTextures) : Entity(renderer)
		{
			loadModel(modelPath, hasTextures);
		}

		Model::~Model()
		{
			dispose();
		}

		void Model::loadModel(const std::string& modelPath, bool hasTextures)
		{
			std::size_t found = modelPath.find_last_of('/');
			_modelDirectory = modelPath.substr(0, found);

			Assimp::Importer importer;
			const aiScene* scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs);

			std::cout << "Loading the 3D model... " << std::endl;

			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
			{
				std::cout << "Error loading the model: " << importer.GetErrorString() << std::endl;
				return;
			}

			processNode(scene->mRootNode, scene, hasTextures);
		}

		void Model::processNode(aiNode* node, const aiScene* scene, bool hasTextures)
		{
			for (int i = 0; i < (int)node->mNumMeshes; i++)
			{
				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
				_modelMeshes.push_back(generateMesh(mesh, scene, hasTextures));
			}

			for (int i = 0; i < (int)node->mNumChildren; i++)
				processNode(node->mChildren[i], scene, hasTextures);
		}

		ModelMesh* Model::generateMesh(aiMesh* mesh, const aiScene* scene, bool hasTextures)
		{
			std::vector<ModelMeshVertex> vertices;
			std::vector<unsigned int> indexes;

			for (int i = 0; i < (int)mesh->mNumVertices; i++)
			{
				ModelMeshVertex vertex;
				aiVector3D aiMeshVertex = mesh->mVertices[i];
				aiVector3D aiMeshNormal = mesh->mNormals[i];
				aiVector3D aiTextCoord(0.0f, 0.0f, 0.0f);

				if (mesh->mTextureCoords[0])
					aiTextCoord = mesh->mTextureCoords[0][i];

				vertex.position = glm::vec3(aiMeshVertex.x, aiMeshVertex.y, aiMeshVertex.z);
				vertex.normal = glm::vec3(aiMeshNormal.x, aiMeshNormal.y, aiMeshNormal.z);
				vertex.uvCoordinates = glm::vec2(aiTextCoord.x, aiTextCoord.y);

				vertices.push_back(vertex);
			}

			for (int i = 0; i < (int)mesh->mNumFaces; i++)
			{
				aiFace face = mesh->mFaces[i];

				for (int j = 0; j < (int)face.mNumIndices; j++)
					indexes.push_back(face.mIndices[j]);
			}

			Material* material = Material::generateMaterial(SIMPLE_VERTEX_SHADER_PATH, SIMPLE_PIXEL_SHADER_PATH);

			if (mesh->mMaterialIndex >= 0 && hasTextures)
			{
				material = Material::generateMaterial(MODEL_TEX_VERTEX_SHADER_PATH, MODEL_TEX_PIXEL_SHADER_PATH);
				aiMaterial* aiMat = scene->mMaterials[mesh->mMaterialIndex];

				std::vector<Texture*> diffuseMaps = loadMaterialTextures(aiMat, aiTextureType_DIFFUSE, "texture_diffuse");
				std::vector<Texture*> specularMaps = loadMaterialTextures(aiMat, aiTextureType_SPECULAR, "texture_specular");

				_textures.insert(_textures.end(), diffuseMaps.begin(), diffuseMaps.end());
				_textures.insert(_textures.end(), specularMaps.begin(), specularMaps.end());

				material->setTexture(diffuseMaps[0], "textureDiffuse");
			}

			return new ModelMesh(_renderer, material, vertices, indexes);
		}

		std::vector<Texture*> Model::loadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName)
		{
			std::vector<Texture*> textures;

			for (int i = 0; i < (int)material->GetTextureCount(type); i++)
			{
				Texture* texture;
				aiString string;
				std::string imagePath;

				material->GetTexture(type, i, &string);
				imagePath = _modelDirectory + "\\" + string.C_Str();
				texture = Texture::generateTexture(imagePath);

				textures.push_back(texture);
			}

			return textures;
		}

		void Model::dispose()
		{
			for (int i = 0; i < (int)_modelMeshes.size(); i++)
				delete _modelMeshes[i];
		}

		void Model::draw() const
		{
			for (int i = 0; i < (int)_modelMeshes.size(); i++)
				_modelMeshes[i]->draw();
		}
	}
}