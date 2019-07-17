#pragma once
#pragma warning(disable: 4251)

#include <string>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "Scene Graph/Component.h"
#include "Core/Exports.h"
#include "Core/EngineConstants.h"

namespace gn
{
	class Renderer;
	class Texture;
	class Material;

	struct MeshVertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 uvCoord;
	};

	class ENGINE_DECL_SPEC MeshRenderer : public Component
	{
	private:
		Renderer* _renderer;
		std::vector<Texture*> _diffuseTextures;
		Material* _material;

		unsigned int _vertexCount;

		float* _vertexBufferData;
		float* _uvBufferData;
		std::vector<unsigned int> _indexBufferData;

		int _vertexBufferID;
		int _uvBufferID;
		int _indexBufferID;

		float* generateVertexBufferData(std::vector<glm::vec3> positions);
		float* generateUVBufferData(std::vector<glm::vec2> uvCoords);
		
		void setIndexBufferData(std::vector<unsigned int> indices);
	
	public:
		MeshRenderer(GameObject* gameObject);
		virtual ~MeshRenderer();

		void start() override;
		void stop() override;
		void draw() const override;

		void createMesh(std::vector<MeshVertex> vertices, std::vector<unsigned int> indices, 
						std::vector<Texture*> diffuseTextures = std::vector<Texture*>());
		void disposeMesh();

		inline std::vector<unsigned int> getIndexBufferData() const { return _indexBufferData; }
		inline std::vector<Texture*> getDiffuseTextures() const { return _diffuseTextures; }
	};
}