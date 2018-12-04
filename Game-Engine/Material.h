#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <glm\mat4x4.hpp>
#include "Texture.h"
#include "Exports.h"

#define SIMPLE_VERTEX_SHADER_PATH "Assets/Shaders/SimpleVertexShader.vertexshader"
#define SIMPLE_PIXEL_SHADER_PATH "Assets/Shaders/SimpleFragmentShader.fragmentshader"
#define CUSTOM_VERTEX_SHADER_PATH "Assets/Shaders/CustomVertexShader.vertexshader"
#define CUSTOM_PIXEL_SHADER_PATH "Assets/Shaders/CustomPixelShader.pixelshader"
#define TEXTURE_VERTEX_SHADER_PATH "Assets/Shaders/TextureVertexShader.vertexshader"
#define TEXTURE_PIXEL_SHADER_PATH "Assets/Shaders/TexturePixelShader.pixelshader"

namespace gn
{
	class Texture;
/*
	A class that is used to generate vertex and pixel shaders that will ultimately define
	the way the entities will look like in the game.
*/
	class ENGINE_API Material
	{
	private:
		Texture* _texture;
	
		unsigned int _programID;
		unsigned int _matrixID;
		unsigned int _textureID;

		Material();
		~Material();
	
		unsigned int loadShaders(const std::string& vertexShaderPath, const std::string& pixelShaderPath);

	public:

		static Material* generateMaterial(const std::string& vertexShaderPath, const std::string& pixelShaderPath);
		static void destroyMaterial(Material* material);
	
		void setMatrixProperty(const char* propertyName, glm::mat4& matrix);
		void setTexture(Texture* texture, const char* propertyName);
		void bind();
		void bindTexture();

		inline unsigned int getTextureWidth() const { return _texture->getWidth(); }
		inline unsigned int getTextureHeight() const { return _texture->getHeight(); }
	};
}