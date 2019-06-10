#pragma once

#include <iostream>
#include <vector>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\mat4x4.hpp>
#include "Exports.h"
#include "Enums.h"

namespace gn
{
	class Window;
/*
	A "Renderer" will handle all of the rendering of the game, taking into considerations tasks such
	as swapping between buffers and manipualating the model, view and projection matrices.
*/
	class ENGINE_API Renderer
	{
	private:
		Window* _renderWindow;
		unsigned int _vertexArrayID;

		glm::mat4 _model;
		glm::mat4 _view;
		glm::mat4 _projection;

		glm::mat4 _orthoProjection;
		glm::mat4 _perspProjection;

		glm::mat4 _mvp;

		void updateMVP();

	public:
		Renderer();
		~Renderer();

		bool start(Window* renderWindow, Projection defaultProjectionType);
		bool stop();
	
		void setClearColor(float r, float g, float b, float a);
		void clearScreen();
		void swapBuffers();
	
		unsigned int generateVertexBuffer(float* vertexBufferData, int size);
		unsigned int generateIndexBuffer(std::vector<unsigned int> indexBufferData, int size);
		void destroyBuffer(unsigned int vertexBufferID);

		void enableAttribute(unsigned int attrib) const;
		void disableAttribute(unsigned int attrib) const;
		void enableBlend() const;
		void disableBlend() const;
		void bindBuffer(unsigned int attrib, unsigned int vertexComponents, unsigned int vertexBufferID) const;
		void bindIndexBuffer(unsigned int vertexBufferID) const;
		void drawBuffer(PrimitiveType primitive, unsigned int vertexCount) const;
		void drawIndexedBuffer(PrimitiveType primitive, unsigned int vertexCount) const;

		void loadIdentityMatrix();
		void setModelMatrix(glm::mat4 matrix);
		void setViewMatrix(glm::mat4 matrix);
		void setProjectionMatrix(glm::mat4 matrix);
		
		void multiplyModelMatrix(glm::mat4 matrix);

		void updateView(float x, float y);
		void updateView(glm::vec3 cameraPos, glm::vec3 center, glm::vec3 upVector);

		void changeOrthoProjection(float left, float right, float bottom, float top, float nearPlane, float farPlane);
		void changePerspProjection(float fieldOfView, float right, float nearPlane, float farPlane);

		void setProjection(Projection projectionType);

		inline glm::mat4& getMVP() { return _mvp; }
		inline glm::mat4& getModelMatrix() { return _model; }
		inline glm::mat4& getViewMatrix() { return _view; }
		inline glm::mat4& getProjectionMatrix() { return _projection; }
		inline Window* getRenderWindow() const { return _renderWindow;  }
	};
}