#include "Texture.h"
#include <GL/glew.h>

Texture::Texture() : _textureID(-1)
{
	cout << "Texture::Texture()" << endl;
}

Texture::~Texture()
{
	cout << "Texture::~Texture()" << endl;
	
	glDeleteTextures(1, &_textureID);
}

unsigned int Texture::loadBMP(const string& imagePath)
{
	cout << "Texture::loadBMP(imagePath)" << endl;

	try
	{
		ifstream bmpFile;
		unsigned char header[BMP_HEADER_SIZE];
		unsigned int dataPosition;
		unsigned int imageSize;
		unsigned char* data;

		bmpFile.open(imagePath, ios::in | ios::binary);
		if (!bmpFile.is_open())
			throw iostream::failure("Could not open the BMP file.");
		bmpFile.read((char*)&header, BMP_HEADER_SIZE);
		if (header[0] != 'B' || header[1] != 'M')
			throw logic_error("The file is not a proper BMP file.");

		_width = *(int*)&header[0x12];
		_height = *(int*)&header[0x16];
		dataPosition =  (*(int*)&header[0x0A] == 0) ? BMP_HEADER_SIZE : *(int*)&header[0x0A];
		imageSize = (*(int*)&header[0x22] == 0) ? _width * _height * 4 : *(int*)&header[0x22];

		bmpFile.seekg(dataPosition, bmpFile.beg);

		data = new unsigned char[imageSize];
		bmpFile.read((char*)data, imageSize);
		cout << "Reading the image..." << endl;
		if (!bmpFile.good())
			throw iostream::failure("There was an error reading the BMP file.");
		bmpFile.close();

		GLuint textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);

		delete[] data;

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
