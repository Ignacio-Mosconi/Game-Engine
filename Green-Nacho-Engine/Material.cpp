#include <GL\glew.h>
#include "Material.h"
#include "Texture.h"

namespace gn
{
	Material::Material() : _texture(NULL), _programID(-1), _matrixID(-1), _textureID(-1)
	{
	}

	Material::~Material()
	{
		glDeleteProgram(_programID);
	}

	unsigned int Material::loadShaders(const std::string& vertexShaderPath, const std::string& pixelShaderPath)
	{
		GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint pixelShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		try
		{
			std::string vertexShaderCode;
			std::ifstream vertexShaderStream(vertexShaderPath, std::ios::in);
			if (!vertexShaderStream.is_open())
				throw std::iostream::failure("The vertex shader file could not be opened");
			std::stringstream vertexStrStream;
			vertexStrStream << vertexShaderStream.rdbuf();
			vertexShaderCode = vertexStrStream.str();
			vertexShaderStream.close();

			std::string pixelShaderCode;
			std::ifstream pixelShaderStream(pixelShaderPath, std::ios::in);
			if (!pixelShaderStream.is_open())
				throw std::iostream::failure("The pixel shader file could not be opened");
			std::stringstream pixelStrStream;
			pixelStrStream << pixelShaderStream.rdbuf();
			pixelShaderCode = pixelStrStream.str();
			pixelShaderStream.close();

			GLint result = GL_FALSE;
			int infoLogLength;

			std::cout << "Compiling vertex shader: " << vertexShaderPath << std::endl;
			const char* vertexSourcePointer = vertexShaderCode.c_str();
			glShaderSource(vertexShaderID, 1, &vertexSourcePointer, NULL);
			glCompileShader(vertexShaderID);

			glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
			glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
			if (infoLogLength > 0)
			{
				std::vector<char> vertexShaderErrorMsg(infoLogLength + 1);
				glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &vertexShaderErrorMsg[0]);
				std::cerr << &vertexShaderErrorMsg[0] << std::endl;
			}

			std::cout << "Compiling pixel shader: " << pixelShaderPath << std::endl;
			const char* pixelSourcePointer = pixelShaderCode.c_str();
			glShaderSource(pixelShaderID, 1, &pixelSourcePointer, NULL);
			glCompileShader(pixelShaderID);

			glGetShaderiv(pixelShaderID, GL_COMPILE_STATUS, &result);
			glGetShaderiv(pixelShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
			if (infoLogLength > 0)
			{
				std::vector<char> pixelShaderErrorMsg(infoLogLength + 1);
				glGetShaderInfoLog(pixelShaderID, infoLogLength, NULL, &pixelShaderErrorMsg[0]);
				std::cerr << &pixelShaderErrorMsg[0] << std::endl;
			}

			std::cout << "Linking the shaders..." << std::endl;
			GLuint programID = glCreateProgram();
			glAttachShader(programID, vertexShaderID);
			glAttachShader(programID, pixelShaderID);
			glLinkProgram(programID);

			glGetProgramiv(programID, GL_LINK_STATUS, &result);
			glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
			if (infoLogLength > 0)
			{
				std::vector<char> programErrorMsg(infoLogLength + 1);
				glGetShaderInfoLog(pixelShaderID, infoLogLength, NULL, &programErrorMsg[0]);
				std::cerr << &programErrorMsg[0] << std::endl;
			}

			glDetachShader(programID, vertexShaderID);
			glDetachShader(programID, pixelShaderID);

			glDeleteShader(vertexShaderID);
			glDeleteShader(pixelShaderID);

			return programID;
		}
		catch (std::iostream::failure& exception)
		{
			std::cerr << exception.what() << std::endl;
			return 0;
		}
	}

	Material* Material::generateMaterial(const std::string& vertexShaderPath, const std::string& pixelShaderPath)
	{
		Material* material = new Material;

		material->_programID = material->loadShaders(vertexShaderPath, pixelShaderPath);

		return material;
	}

	void Material::destroyMaterial(Material* material)
	{
		if (material)
			delete material;
	}

	void Material::bind()
	{
		glUseProgram(_programID);
	}

	void Material::setMatrixProperty(const char* propertyName, glm::mat4& matrix)
	{
		_matrixID = glGetUniformLocation(_programID, propertyName);

		glUniformMatrix4fv(_matrixID, 1, GL_FALSE, &matrix[0][0]);
	}

	void Material::setTexture(Texture* texture, const char* propertyName)
	{
		_texture = texture;
		_textureID = glGetUniformLocation(_programID, propertyName);
	}

	void Material::bindTexture()
	{
		if (_textureID != -1)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, _texture->getTexureID());
			glUniform1i(_textureID, 0);
		}
	}
}