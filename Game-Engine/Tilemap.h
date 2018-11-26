#pragma once

#include <iostream>
#include <fstream>
#include <glm.hpp>

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
	TileType tileType;
	float* vertexBufferData;
	float* uvBufferData;
	unsigned int vertexBufferID;
	unsigned int uvBufferID;
};

class ENGINE_API Tilemap
{
private:
	Renderer* _renderer;
	Texture* _tileset;
	Material* _material;
	
	Tile** _tiles;
	Tile** _onScreenTiles;
	int** _level;

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

	Tile** loadTiles(unsigned int rows, unsigned int columns);
	Tile** createOnScreenTiles();
/*	
Used to parse a CSV-exported "oel" file made with the Ogmo Editor; make sure the tileset's empty tiles are
are actually filled with a transparent tile at the "0" index for the loader to work properly.
*/
	int** loadLevelCSV(const string& levelPath);
	
	float* setTileVerticesUV(unsigned int x, unsigned int y) const;
	float* setOnScreenTileVertices(unsigned int x, unsigned int y) const;

public:
	Tilemap(Renderer* renderer, const string& tilesetPath, const string& levelPath,
			int levelWidth, int levelHeight, int tileWidth, int tileHeight, unsigned int tilesetRows, unsigned int tilesetColumns);
	~Tilemap();
	
	void setTileInfo(unsigned int tileIndex, TileType tileType);
	void setOnScreenTiles();
	Tile getTile(unsigned int tileIndex);

	void draw() const;
};