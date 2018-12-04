#pragma once

#include <string>
#include <map>
#include <glm.hpp>
#include "Exports.h"

#define TEXTURE_VERTEX_SHADER_PATH "Assets/Shaders/TextureVertexShader.vertexshader"
#define TEXTURE_PIXEL_SHADER_PATH "Assets/Shaders/TexturePixelShader.pixelshader"

using namespace std;
using namespace glm;

class Renderer;
class Material;
class Texture;
class Sprite;
class BoundingBox;
class Animation;
class Tilemap;

/*
A complex class that is meant to be used as a base for all the characters and/or interactables of a game;
they contain a "Sprite" (for rendering) and a "BoundingBox" (for collision detection), and they also have
the possibility to include animations.
*/

class ENGINE_API GameEntity
{
private:
	Sprite* _sprite;
	BoundingBox* _boundingBox;
	
	mutable map<string, Animation*> _animations;

	Material* _material;
	Texture* _texture;

	Tilemap* _tilemap;

	Sprite* createSprite(Renderer* renderer, const string& imagePath, int spriteRows = 1, int spriteColumns = 1, 
		int frameWidth = -1, int frameHeight = -1);
	void createBoundingBox(float width, float height, bool isStatic, float mass, const string& collisionLayer);

public:
	GameEntity(Renderer* renderer, const string& imagePath, const string& collisionLayer);
	GameEntity(Renderer* renderer, Tilemap* tilemap, const string& imagePath, const string& collisionLayer,
				float x, float y, int spriteRows, int spriteColumns, int frameWidth, int frameHeight, 
				bool isStatic = false, float mass = 1);
	~GameEntity();

	void setBoundingBoxDimensions(float width, float height);

	void addAnimation(Animation* animation, const string& animName);

	void move(float x, float y, float z = 0.0f);

	virtual void update(float deltaTime);
	virtual void draw() const;

	inline Animation* getCurrentAnimation() const;
	inline Sprite* getSprite() const { return _sprite; }
	inline BoundingBox* getBoundingBox() const { return _boundingBox; }
};