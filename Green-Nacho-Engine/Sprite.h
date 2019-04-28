#pragma once

#include "Shape.h"

namespace gn
{
/*
	A fairly complex class that displays a texture; it may have a spritesheet texture in order
	to display different parts of an image - allowing the implementation of animations.
*/
	class ENGINE_API Sprite : public Shape
	{
	private:
		float* _uvBufferData;
	
		unsigned int _uvBufferID;
		
		unsigned int _frameID;
		unsigned int _rows;
		unsigned int _columns;
		
		float _frameWidth;
		float _frameHeight;

	protected:
		bool create(unsigned int vertexCount, float* colorBufferData = NULL) override;
		
		float* generateVertexBufferData() const override;
		float* generateUVBufferData(float x, float y) const;

	public:
		Sprite(Renderer* renderer, Material* material, float frameWidth, float frameHeight, unsigned int rows = 0, unsigned int columns = 0);
		~Sprite();

		void setAnimationFrame(unsigned int id);
		void setFramesInfo(unsigned int rows, unsigned int columns, float frameWidth, float frameHeight);

		virtual void dispose() override;
	
		void draw() const override;

		inline float getFrameWidth() const { return _frameWidth; }
		inline float getFrameHeight() const { return _frameHeight; }
	};
}