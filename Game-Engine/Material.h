#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <glm.hpp>
#include "Exports.h"
using namespace std;
using namespace glm;

class Texture;

class ENGINE_API Material
{
private:
	Texture* _texture;
	unsigned int _programID;
	unsigned int _matrixID;
	unsigned int _textureID;

	Material();
	~Material();
	unsigned int loadShaders(const string& vertexShaderPath, const string& pixelShaderPath);

public:

	static Material* generateMaterial(const string& vertexShaderPath, const string& pixelShaderPath);
	static void destroyMaterial(Material* material);
	void setMatrixProperty(const char* propertyName, mat4& matrix);
	void setTexture(Texture* texture, const char* propertyName);
	void bind();
	void bindTexture();
};