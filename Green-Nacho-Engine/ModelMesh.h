#pragma once

#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "Entity.h"
#include "Renderer.h"
#include "Material.h"
#include "Exports.h"

namespace gn
{
	struct ModelMeshVertex
	{
		glm::vec3 position;
		glm::vec2 uvCoordinates;
	};

	class ENGINE_API ModelMesh : public Entity
	{
	private:
		//Material* _material;

		std::vector<ModelMeshVertex> _vertices;
		std::vector<unsigned short> _indexes;

		unsigned int _vertexBufferID;
		unsigned int _uvBufferID;
		unsigned int _indexBufferID;

		void create();

	public:
		ModelMesh(Renderer* renderer, std::vector<ModelMeshVertex> vertices, std::vector<unsigned short> indexes);
		virtual ~ModelMesh();

		void draw() const;
	};
}