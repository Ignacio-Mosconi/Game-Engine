#pragma once

#include <iostream>
#include <glm.hpp>
#include "Exports.h"
using namespace std;
using namespace glm;

class Window;

class ENGINE_API Renderer
{
private:
	Window* _renderWindow;
	unsigned int _vertexArrayID;

	mat4 _model;
	mat4 _view;
	mat4 _projection;

	mat4 _mvp;

	void updateMVP();

public:
	Renderer();
	~Renderer();

	bool start(Window* renderWindow);
	bool stop();
	
	void setClearColor(float r, float g, float b, float a);
	void clearScreen();
	void swapBuffers();
	
	unsigned int generateVertexBuffer(float* vertexBufferData, int size);
	void destroyVertexBuffer(unsigned int vertexBufferID);
	void drawBuffer(unsigned int vertexBufferID, int vertexCount) const;

	void loadIdentityMatrix();
	void setModelMatrix(mat4 matrix);
	void multiplyModelMatrix(mat4 matrix);

	inline mat4& getMVP() { return _mvp; }
};