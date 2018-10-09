#pragma once

#include <iostream>
#include <fstream>
#include "Exports.h"

#define BMP_HEADER_SIZE 54

using namespace std;

class ENGINE_API Texture
{
private:
	unsigned int _textureID;

	Texture();
	~Texture();

	unsigned int loadBMP(const string& imagePath);

public:
	static Texture* generateTextureBMP(const string& imagePath);
	static void destroyTexture(Texture* texture);

	inline unsigned int getTexureID() const { return _textureID; }
};