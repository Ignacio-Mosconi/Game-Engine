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
	GameEntity(Renderer* renderer, string& imagePath);
	GameEntity(Renderer* renderer, string& imagePath, float x, float y);
	~GameEntity();

	Sprite* createSprite(Renderer* renderer, string& imagePath);
	void setBoundingBoxDimensions(float width, float height);
	
	static Material* getTextureMaterial();

	inline BoundingBox* getBoundingBox() const { return _boundingBox; }
};