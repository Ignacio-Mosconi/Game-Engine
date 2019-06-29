#pragma once

#include <iostream>
#include <fstream>
#include "Exports.h"
#include "EngineConstants.h"

namespace gn
{
/*
	A class used to store the information related to an image in the bitmap format.
*/
	class ENGINE_DECL_SPEC Texture
	{
	private:
		unsigned int _textureID;
		unsigned int _width;
		unsigned int _height;

		Texture();
		~Texture();

		unsigned int loadBMP(const std::string& imagePath);
		unsigned int load(const std::string& imagePath);
		unsigned int load(unsigned char imageData[]);

	public:
		static Texture* generateTextureBMP(const std::string& imagePath);
		static Texture* generateTexture(const std::string& imagePath);
		static Texture* generateTexture(unsigned char imageData[]);
		static void destroyTexture(Texture* texture);

		inline unsigned int getTexureID() const { return _textureID; }
		inline unsigned int getWidth() const { return _width; }
		inline unsigned int getHeight() const { return _height; }
	};
}