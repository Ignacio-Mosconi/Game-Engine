#include "Renderer.h"
#include "Window.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>

namespace gn
{
	Renderer::Renderer()
	{
		std::cout << "Renderer::Renderer()" << std::endl;
	}

	Renderer::~Renderer()
	{
		std::cout << "Renderer::~Renderer()" << std::endl;
	}

	void Renderer::updateMVP()
	{
		_mvp = _projection * _view * _model;
	}

	bool Renderer::start(Window* renderWindow, ProjectionType defaultProjection)
	{
		std::cout << "Renderer::start(renderWindow)" << std::endl;

		_renderWindow = renderWindow;

		glfwMakeContextCurrent((GLFWwindow*)_renderWindow->getWindowPtr());

		if (glewInit() != GLEW_OK)
		{
			std::cerr << "Failed to initialize Glew." << std::endl;
			return false;
		}

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glGenVertexArrays(1, &_vertexArrayID);
		glBindVertexArray(_vertexArrayID);

		_model = glm::mat4(1.0f);
		_view = glm::lookAt(glm::vec3(0.0f, 0.0f, 1000.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		float windowWidth = (float)_renderWindow->getWidth();
		float windowHeight = (float)_renderWindow->getHeight();
		
		_orthoProjection = glm::ortho(0.0f, windowWidth, 0.0f, windowHeight, 0.0f, 1.0f);
		_perspProjection = glm::perspective(glm::radians(45.0f), windowWidth / windowHeight, 0.1f, 1000.0f);

		setProjectionType(defaultProjection);

		return true;
	}

	bool Renderer::stop()
	{
		std::cout << "Renderer::stop()" << std::endl;

		glDeleteVertexArrays(1, &_vertexArrayID);

		return true;
	}

	void Renderer::setClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void Renderer::clearScreen()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::swapBuffers()
	{
		glfwSwapBuffers((GLFWwindow*)_renderWindow->getWindowPtr());
	}

	unsigned int Renderer::generateVertexBuffer(float* vertexBufferData, int size)
	{
		GLuint vertexBuffer;

		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, size, vertexBufferData, GL_STATIC_DRAW);

		return vertexBuffer;
	}	
	
	unsigned int Renderer::generateIndexBuffer(std::vector<unsigned short> indexBufferData, int size)
	{
		GLuint vertexBuffer;

		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, &indexBufferData[0], GL_STATIC_DRAW);

		return vertexBuffer;
	}

	void Renderer::destroyBuffer(unsigned int bufferID)
	{
		glDeleteBuffers(1, &bufferID);
	}

	void Renderer::enableAttribute(unsigned int attrib) const
	{
		glEnableVertexAttribArray(attrib);
	}

	void Renderer::disableAttribute(unsigned int attrib) const
	{
		glDisableVertexAttribArray(attrib);
	}

	void Renderer::enableBlend() const
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Renderer::disableBlend() const
	{
		glDisable(GL_BLEND);
	}

	void Renderer::bindBuffer(unsigned int attrib, unsigned int vertexComponents, unsigned int vertexBufferID) const
	{
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glVertexAttribPointer(attrib, vertexComponents, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}	
	
	void Renderer::bindIndexBuffer(unsigned int indexBufferID) const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	}

	void Renderer::drawBuffer(PrimitiveType primitive, unsigned int vertexCount) const
	{
		glDrawArrays((int)primitive, 0, vertexCount);
	}	
	
	void Renderer::drawIndexedBuffer(PrimitiveType primitive, unsigned int indexesSize) const
	{
		glDrawElements((int)primitive, indexesSize, GL_UNSIGNED_SHORT, (void*)0);
	}

	void Renderer::loadIdentityMatrix()
	{
		_model = glm::mat4(1.0f);
		updateMVP();
	}

	void Renderer::setModelMatrix(glm::mat4 matrix)
	{
		_model = matrix;
		updateMVP();
	}

	void Renderer::multiplyModelMatrix(glm::mat4 matrix)
	{
		_model *= matrix;
		updateMVP();
	}

	void Renderer::updateView(float x, float y)
	{
		glm::vec3 newCameraPos(x, y, 1.0f);
	
		_view = glm::lookAt(newCameraPos, glm::vec3(newCameraPos.x, newCameraPos.y, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		updateMVP();
	}

	void Renderer::updateView(glm::vec3 cameraPos, glm::vec3 center, glm::vec3 upVector)
	{
		_view = glm::lookAt(cameraPos, center, upVector);

		updateMVP();
	}

	void Renderer::changeOrthoProjection(float left, float right, float bottom, float top, float nearPlane, float farPlane)
	{
		bool updateProjection = (_projection == _orthoProjection) ? true : false;

		_orthoProjection = glm::ortho(left, right, bottom, top, nearPlane, farPlane);

		if (updateProjection)
			updateMVP();
	}

	void Renderer::changePerspProjection(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
	{
		bool updateProjection = (_projection == _perspProjection) ? true : false;

		_perspProjection = glm::perspective(glm::radians(fieldOfView), aspectRatio, nearPlane, farPlane);

		if (updateProjection)
			updateMVP();
	}

	void Renderer::setProjectionType(ProjectionType projectionType)
	{
		switch (projectionType)
		{
			case ProjectionType::ORTHOGRAPHIC:
				_projection = _orthoProjection;
				break;
			case ProjectionType::PERSPECTIVE:
				_projection = _perspProjection;
				break;
			default:
				_projection = _orthoProjection;
				break;
		}

		updateMVP();
	}
}