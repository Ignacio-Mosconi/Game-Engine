#pragma once

#include <iostream>
#include <glm.hpp>
#include "Exports.h"
using namespace std;
using namespace glm;

class Window;

enum PrimitiveType
{
	TRIANGLE = 4,
	TRIANGLE_STRIP = 5,
	TRIANGLE_FAN = 6
};

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

	void enableAttribute(unsigned int attrib) const;
	void disableAttribute(unsigned int attrib) const;
	void enableBlend() const;
	void disableBlend() const;
	void bindBuffer(unsigned int attrib, unsigned int vertexComponents, unsigned int vertexBufferID) const;
	void drawBuffer(PrimitiveType primitive, unsigned int vertexCount) const;

	void loadIdentityMatrix();
	void setModelMatrix(mat4 matrix);
	void multiplyModelMatrix(mat4 matrix);

	inline mat4& getMVP() { return _mvp; }
};