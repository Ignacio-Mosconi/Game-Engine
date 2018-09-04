#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "Exports.h"
using namespace std;

class ENGINE_API Material
{
private:
	unsigned int _programID;

	Material();
	unsigned int loadShaders(const string& vertexShaderPath, const string& pixelShaderPath);

public:
	~Material();

	static Material* generateMaterial(const string& vertexShaderPath, const string& pixelShaderPath);
	void bind();
};

