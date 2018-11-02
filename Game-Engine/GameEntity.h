#pragma once

#include <string>
#include <glm.hpp>
#include "Exports.h"

#define TEXTURE_VERTEX_SHADER_PATH "Shaders/TextureVertexShader.vertexshader"
#define TEXTURE_PIXEL_SHADER_PATH "Shaders/TexturePixelShader.pixelshader"

using namespace std;
using namespace glm;

class Renderer;
class Material;
class Texture;
class Sprite;
class BoundingBox;

class ENGINE_API GameEntity
{
private:
	Sprite* _sprite;
	BoundingBox* _boundingBox;

	static Material* _textureMaterial;
	Texture* _texture;

public:
	GameEntity(Renderer* renderer, string& imagePath, string& collisionLayer);
	GameEntity(Renderer* renderer, string& imagePath, string& collisionLayer, float x, float y,
				int spriteRows, int spriteColumns, int frameWidth, int frameHeight, bool isStatic = false, float mass = 1);
	~GameEntity();

	Sprite* createSprite(Renderer* renderer, string& imagePath, int spriteRows = 1, int spriteColumns = 1, 
		int frameWidth = -1, int frameHeight = -1);
	void setBoundingBoxDimensions(float width, float height);
	
	static Material* getTextureMaterial();

	void draw() const;

	inline Sprite* getSprite() const { return _sprite; }
	inline BoundingBox* getBoundingBox() const { return _boundingBox; }
};