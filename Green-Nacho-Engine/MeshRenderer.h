#pragma once

#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "Component.h"
#include "Exports.h"
#include "EngineConstants.h"

namespace gn
{
	class Renderer;
	class Texture;
	class Material;

	struct MeshVertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 uvCoords;
	};

	class ENGINE_API MeshRenderer : public Component
	{
	private:
		Renderer* _renderer;
		Texture* _texture;
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
		MeshRenderer();
		virtual ~MeshRenderer();

		void start() override;
		void stop() override;
		void draw() const override;

		void createMesh(Renderer* renderer, std::vector<MeshVertex> vertices, std::vector<unsigned int> indices);
		void disposeMesh();
	};
}