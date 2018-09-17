#include "Material.h"
#include <GL/glew.h>

Material::Material()
{
	cout << "Material::Material()" << endl;
}

Material::~Material()
{
	cout << "Material::~Material()" << endl;

	glDeleteProgram(_programID);
}

unsigned int Material::loadShaders(const string& vertexShaderPath, const string& pixelShaderPath)
{
	cout << "Material::loadShaders(vertexShaderPath, pixelShaderPath)" << endl;

	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint pixelShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	try
	{
		string vertexShaderCode;
		ifstream vertexShaderStream(vertexShaderPath, ios::in);
		if (!vertexShaderStream.is_open())
			throw iostream::failure("The vertex shader file could not be opened");
		stringstream vertexStrStream;
		vertexStrStream << vertexShaderStream.rdbuf();
		vertexShaderCode = vertexStrStream.str();
		vertexShaderStream.close();

		string pixelShaderCode;
		ifstream pixelShaderStream(pixelShaderPath, ios::in);
		if (!pixelShaderStream.is_open())
			throw iostream::failure("The pixel shader file could not be opened");
		stringstream pixelStrStream;
		pixelStrStream << pixelShaderStream.rdbuf();
		pixelShaderCode = pixelStrStream.str();
		pixelShaderStream.close();

		GLint result = GL_FALSE;
		int infoLogLength;

		cout << "Compiling vertex shader: " << vertexShaderPath << endl;
		const char* vertexSourcePointer = vertexShaderCode.c_str();
		glShaderSource(vertexShaderID, 1, &vertexSourcePointer, NULL);
		glCompileShader(vertexShaderID);

		glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
		glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			vector<char> vertexShaderErrorMsg(infoLogLength + 1);
			glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &vertexShaderErrorMsg[0]);
			cerr << &vertexShaderErrorMsg[0] << endl;
		}

		cout << "Compiling pixel shader: " << pixelShaderPath << endl;
		const char* pixelSourcePointer = pixelShaderCode.c_str();
		glShaderSource(pixelShaderID, 1, &pixelSourcePointer, NULL);
		glCompileShader(pixelShaderID);

		glGetShaderiv(pixelShaderID, GL_COMPILE_STATUS, &result);
		glGetShaderiv(pixelShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			vector<char> pixelShaderErrorMsg(infoLogLength + 1);
			glGetShaderInfoLog(pixelShaderID, infoLogLength, NULL, &pixelShaderErrorMsg[0]);
			cerr << &pixelShaderErrorMsg[0] << endl;
		}

		cout << "Linking the shaders..." << endl;
		GLuint programID = glCreateProgram();
		glAttachShader(programID, vertexShaderID);
		glAttachShader(programID, pixelShaderID);
		glLinkProgram(programID);

		glGetProgramiv(programID, GL_LINK_STATUS, &result);
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			vector<char> programErrorMsg(infoLogLength + 1);
			glGetShaderInfoLog(pixelShaderID, infoLogLength, NULL, &programErrorMsg[0]);
			cerr << &programErrorMsg[0] << endl;
		}

		glDetachShader(programID, vertexShaderID);
		glDetachShader(programID, pixelShaderID);

		glDeleteShader(vertexShaderID);
		glDeleteShader(pixelShaderID);

		return programID;
	}
	catch (iostream::failure& exception)
	{
		cerr << exception.what() << endl;
	}
}

Material* Material::generateMaterial(const string& vertexShaderPath, const string& pixelShaderPath)
{
	cout << "Material::generateMaterial(vertexShaderPath, pixelShaderPath)" << endl;

	Material* material = new Material;

	material->_programID = material->loadShaders(vertexShaderPath, pixelShaderPath);

	return material;
}

void Material::bind()
{
	cout << "Material::bind()" << endl;

	glUseProgram(_programID);
}

void Material::setMatrixProperty(const char* propertyName, mat4& matrix)
{
	_matrixID = glGetUniformLocation(_programID, propertyName);

	glUniformMatrix4fv(_matrixID, 1, GL_FALSE, &matrix[0][0]);
}
