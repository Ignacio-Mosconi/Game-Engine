#pragma once

#include <string>
#include "Scene Graph/Component.h"
#include "Core/Exports.h"

namespace gn
{
	class Renderer;
	class Material;
	class Texture;

	class ENGINE_DECL_SPEC SpriteRenderer : public Component
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
		SpriteRenderer();
		virtual ~SpriteRenderer();

		void start() override;
		void stop() override;
		void draw() const override;

		void createSprite(Renderer* renderer, const std::string& spritePath, unsigned int rows = 1, unsigned int columns = 1);
		void disposeSprite();

		void setFramesInfo(unsigned int rows, unsigned int columns, float frameWidth, float frameHeight);
	};
}