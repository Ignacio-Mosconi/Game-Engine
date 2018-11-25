#pragma once

#include <iostream>
#include <fstream>
#include <glm.hpp>

#include "Exports.h"

#define TEXTURE_VERTEX_SHADER_PATH "Shaders/TextureVertexShader.vertexshader"
#define TEXTURE_PIXEL_SHADER_PATH "Shaders/TexturePixelShader.pixelshader"
#define CHARS_BUFFER_SIZE 64

using namespace std;

class Texture;
class Material;

class ENGINE_API Tilemap
{
private:
	Texture* _tileset;
	Material* _material;
	
	int** _level;

public:
	Tilemap(const string& tilesetPath, const string& levelPath, int levelWidth, int levelHeight, int tileWidth, int tileHeight);
	~Tilemap();

/*	
Used to parse a CSV-exported "oel" file made with the Ogmo Editor; make sure the tileset's empty tiles are
are actually filled with a transparent tile at the "0" index for the loader to work properly.
*/
	int** loadLevelCSV(const string& levelPath, int levelWidth, int levelHeight, int tileWidth, int tileHeight);
};