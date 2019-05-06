#include "Model.h"
#include "ModelMesh.h"
#include "Material.h"

namespace gn
{
	Model::Model(Renderer* renderer, const char* modelPath) : Entity(renderer)
	{
		loadModel(modelPath);
	}

	Model::~Model()
	{
		dispose();
	}

	void Model::loadModel(const std::string& modelPath)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs);

		std::cout << "Loading the 3D model... " << std::endl;

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
		std::vector<unsigned int> indexes;

		for (int i = 0; i < mesh->mNumVertices; i++)
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

		for (int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];

			for (int j = 0; j < face.mNumIndices; j++)
				indexes.push_back(face.mIndices[j]);
		}

		Material* testMaterial = Material::generateMaterial(SIMPLE_VERTEX_SHADER_PATH, SIMPLE_PIXEL_SHADER_PATH);

		//for (int i = 0; i < vertices.size(); i++)
		//{
		//	unsigned int index;
		//	bool similarVertexFound = getSimilarVertex(vertices[i], vertexMap, index);

		//	if (!similarVertexFound)
		//	{
		//		index = (unsigned int)outputVertices.size();			
		//		outputVertices.push_back(vertices[i]);
		//		vertexMap[vertices[i]] = index;
		//	}
		//	
		//	indexes.push_back(index);
		//}

		return ModelMesh(_renderer, testMaterial, vertices, indexes);
	}

	//bool Model::getSimilarVertex(ModelMeshVertex& vertex, std::map<ModelMeshVertex, 
	//							unsigned int>& vertexMap, unsigned int& resultingIndex) const
	//{
	//	bool found = false;

	//	std::map<ModelMeshVertex, unsigned int>::iterator it = vertexMap.find(vertex);

	//	if (it != vertexMap.end())
	//	{
	//		resultingIndex = it->second;
	//		found = true;
	//	}

	//	return found;
	//}

	void Model::dispose()
	{
		for (int i = 0; i < _modelMeshes.size(); i++)
			_modelMeshes[i].dispose();
	}

	void Model::draw() const
	{
		for (int i = 0; i < _modelMeshes.size(); i++)
			_modelMeshes[i].draw();
	}
}