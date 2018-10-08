#include "Texture.h"
#include <GL/glew.h>

Texture::Texture()
{
	cout << "Texture::Texture()" << endl;
}

Texture::~Texture()
{
	cout << "Texture::~Texture()" << endl;
}

unsigned int Texture::loadBMP(const string& imagePath)
{
	cout << "Texture::loadBMP(imagePath)" << endl;

	try
	{
		ifstream bmpFile;
		char header[BMP_HEADER_SIZE];
		unsigned int dataPosition;
		unsigned int width;
		unsigned int height;
		unsigned int imageSize;
		char* data;

		bmpFile.open(imagePath, ios::in | ios::binary);
		if (!bmpFile.is_open())
			throw iostream::failure("Could not open the BMP file.");
		bmpFile.read(header, BMP_HEADER_SIZE);
		if (header[0] != 'B' || header[1] != 'M')
			throw logic_error("The file is not a proper BMP file.");

		width = (unsigned int)header[0x12];
		height = (unsigned int)header[0x16];
		dataPosition = (unsigned int)(header[0x0A] == BMP_HEADER_SIZE) ? (unsigned int)header[0x0A] : BMP_HEADER_SIZE;
		imageSize = (unsigned int)(header[0x22] == width * height * 3) ? (unsigned int)header[0x22] : width * height * 3;

		data = new char[imageSize];
		bmpFile.read(data, imageSize);
		cout << "Reading the image..." << endl;
		if (!bmpFile.good())
			throw iostream::failure("There was an error reading the BMP file.");
		bmpFile.close();

		GLuint textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		return textureID;
	}
	catch (iostream::failure& exception)
	{
		cerr << exception.what() << endl;
	}
	catch (logic_error& exception)
	{
		cerr << exception.what() << endl;
	}
}

Texture* Texture::generateTextureBMP(const string& imagePath)
{
	cout << "Texture::generateTextureBMP(imagePath)" << endl;

	Texture* texture = new Texture;

	texture->_textureID = texture->loadBMP(imagePath);

	return texture;
}

void Texture::destroyTexture(Texture* texture)
{
	cout << "Texture::destroyTexture(texture)" << endl;

	if (texture)
		delete texture;
}
