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
	static const int vertices = 4;
	static const int vertexComponents = 3;
	
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
	
	unsigned int _tileWidth;
	unsigned int _tileHeight;
	
	unsigned int _tilesRows;
	unsigned int _tilesColumns;
	
	unsigned int _onScreenTilesRows;
	unsigned int _onScreenTilesColumns;

	unsigned int _levelRows;
	unsigned int _levelColumns;

	Tile** loadTiles(unsigned int rows, unsigned int columns, int tileWidth, int tileHeight);
	Tile** createOnScreenTiles();
	int** loadLevelCSV(const string& levelPath); // Used to parse a CSV - exported "oel" file made with the Ogmo Editor; 
												// make sure the tileset's empty tiles are are actually filled with a transparent
												// tile at the "0" index for the loader to work properly.

	float* setOnScreenTilesVertices(int totalTiles) const;
	Tile getTile(unsigned int tileIndex) const;

public:
	Tilemap(Renderer* renderer, const string& tilesetPath, const string& levelPath,
			int levelWidth, int levelHeight, int tileWidth, int tileHeight, unsigned int tilesetRows, unsigned int tilesetColumns);
	~Tilemap();
	
	//void setTileInfo(unsigned int tileIndex, TileType tileType);

	void updateVerticesUV();
	void draw() const override;
};