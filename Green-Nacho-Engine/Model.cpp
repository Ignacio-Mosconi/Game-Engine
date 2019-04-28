#include "Model.h"
#include "ModelMesh.h"

namespace gn
{
	Model::Model(Renderer* renderer, const char* modelPath) : Entity(renderer)
	{
		loadModel(modelPath);
	}

	Model::~Model()
	{

	}

	void Model::loadModel(const std::string& modelPath)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "Error loading the model: " << importer.GetErrorString() << std::endl;
			return;
		}

		processNode(scene->mRootNode, scene);
	}

	void Model::processNode(aiNode* node, const aiScene* scene)
	{
		for (int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			_modelMeshes.push_back(generateMesh(mesh, scene));
		}

		for (int i = 0; i < node->mNumChildren; i++)
			processNode(node->mChildren[i], scene);
	}	
	
	ModelMesh Model::generateMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<ModelMeshVertex> vertices;
		std::vector<unsigned short> indexes;

		for (int i = 0; i < mesh->mNumVertices; i++)
		{
			ModelMeshVertex vertex;
			aiVector3D aiMeshVertex = mesh->mVertices[i];
			aiVector3D aiTextCoord(0.0f, 0.0f, 0.0f);

			if (mesh->mTextureCoords[0])
				aiTextCoord = mesh->mTextureCoords[0][i];

			vertex.position = glm::vec3(aiMeshVertex.x, aiMeshVertex.y, aiMeshVertex.z);
			vertex.uvCoordinates = glm::vec2(aiTextCoord.x, aiTextCoord.y);

			vertices.push_back(vertex);
		}

		for (int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];

			for (int j = 0; j < face.mNumIndices; j++)
				indexes.push_back(face.mIndices[j]);
		}

		return ModelMesh(_renderer, vertices, indexes);
	}

	void Model::draw() const
	{
		for (int i = 0; i < _modelMeshes.size(); i++)
			_modelMeshes[i].draw();
	}
}