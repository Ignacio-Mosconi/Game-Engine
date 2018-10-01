#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <glm.hpp>
#include "Exports.h"
using namespace std;
using namespace glm;

class ENGINE_API Material
{
private:
	unsigned int _programID;
	unsigned int _matrixID;

	Material();
	unsigned int loadShaders(const string& vertexShaderPath, const string& pixelShaderPath);

public:
	~Material();

	static Material* generateMaterial(const string& vertexShaderPath, const string& pixelShaderPath);
	static void destroyMaterial(Material* material);
	void setMatrixProperty(const char* propertyName, mat4& matrix);
	void bind();
};

