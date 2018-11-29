#pragma once

#include <iostream>
#include <fstream>
#include <glm.hpp>

#include "Entity.h"
#include "Exports.h"

#define TEXTURE_VERTEX_SHADER_PATH "Assets/Shaders/TextureVertexShader.vertexshader"
#define TEXTURE_PIXEL_SHADER_PATH "Assets/Shaders/TexturePixelShader.pixelshader"
#define CHARS_BUFFER_SIZE 64

using namespace std;
using namespace glm;

class Texture;
class Material;
class Renderer;

enum TileType
{
	Background, Wall
};

struct Tile
{
	static const int vertexAmount = 4;
	static const int vertexComponents = 3;
	
	static unsigned int tileWidth;
	static unsigned int tileHeight;
	
	TileType tileType;
	float* uvVertices;
};

class ENGINE_API Tilemap : public Entity
{
private:
	Texture* _texture;
	Material* _material;
	
	Tile** _tiles;
	Tile** _onScreenTiles;
	int** _level;

	float* _vertexBufferData;
	float* _uvBufferData;
	unsigned int _vertexBufferID;
	unsigned int _uvBufferID;

	unsigned int _levelWidth;
	unsigned int _levelHeight;
	
	unsigned int _tilesRows;
	unsigned int _tilesColumns;
	
	unsigned int _onScreenTilesRows;
	unsigned int _onScreenTilesColumns;

	unsigned int _levelRows;
	unsigned int _levelColumns;

	int** loadLevelCSV(const string& levelPath);
	Tile** loadTiles(unsigned int rows, unsigned int columns, int tileWidth, int tileHeight);
	
	Tile** createOnScreenTiles();

	float* setOnScreenTilesVertices(int totalTiles) const;
	float* createUvBuffer() const;
	

public:
	Tilemap(Renderer* renderer, const string& tilesetPath, const string& levelPath,
			int levelWidth, int levelHeight, int tileWidth, int tileHeight, unsigned int tilesetRows, unsigned int tilesetColumns);
	~Tilemap();

	void setTileProperty(unsigned int tyleIndex, TileType tileType);

	void updateVerticesUV();
	
	void draw() const override;

	Tile getTile(unsigned int tileIndex) const;
	TileType getTileType(unsigned int row, unsigned int column) const;
	
	vec2 worldToGrid(float posX, float posY) const;
	vec2 gridToWorld(unsigned int row, unsigned int col) const;
};