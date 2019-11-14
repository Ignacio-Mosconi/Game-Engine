#pragma once
#pragma warning(disable: 4251)

#include <string>
#include <vector>
#include <map>
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

	struct CustomBufferData
	{
		float* bufferData;
		unsigned int components;
		int bufferID;
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
		
		std::map<int, CustomBufferData> _customBufferDataByAttribute;

		int _vertexBufferID;
		int _uvBufferID;
		int _indexBufferID;

		float* generateVertexBufferData(std::vector<glm::vec3> positions);
		float* generateUVBufferData(std::vector<glm::vec2> uvCoords);
		float* generateCustomBufferData(std::vector<float*> values, int components);
		
		void setIndexBufferData(std::vector<unsigned int> indices);
	
	public:
		MeshRenderer(GameObject* gameObject);
		virtual ~MeshRenderer();

		void start() override;
		void stop() override;
		void draw() const override;

		void createMesh(std::vector<MeshVertex> vertices, std::vector<unsigned int> indices, 
						std::vector<Texture*> diffuseTextures = std::vector<Texture*>(),
						const std::string& vertexShaderPath = MODEL_TEX_VERTEX_SHADER_PATH,
						const std::string& pixelShaderPath = MODEL_TEX_PIXEL_SHADER_PATH);
		void disposeMesh();

		void addCustomBuffer(const int& attribute, std::vector<float*> values, const int& components);

		inline std::vector<unsigned int> getIndexBufferData() const { return _indexBufferData; }
		inline std::vector<Texture*> getDiffuseTextures() const { return _diffuseTextures; }
	};
}