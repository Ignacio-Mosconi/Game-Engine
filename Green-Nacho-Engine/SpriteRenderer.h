#pragma once

#include <string>
#include "Component.h"
#include "Exports.h"

namespace gn
{
	class Renderer;
	class Material;
	class Texture;

	class ENGINE_API SpriteRenderer : public Component
	{
	private:
		Renderer* _renderer;
		Texture* _texture;
		Material* _material;

		float* _vertexBufferData;
		float* _uvBufferData;

		int _vertexBufferID;
		int _uvBufferID;

		unsigned int _frameID;
		unsigned int _rows;
		unsigned int _columns;

		float _frameWidth;
		float _frameHeight;

		float* generateVertexBufferData() const;
		float* generateUVBufferData(float x, float y) const;

	public:
		SpriteRenderer(Renderer* renderer, const std::string& spritePath,
			unsigned int rows = 0, unsigned int columns = 0);
		~SpriteRenderer();

		void start() override;
		void stop() override;
		void update() override;
		void draw(glm::mat4 modelMatrix) const override;
	};
}
