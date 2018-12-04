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

	bool Renderer::start(Window* renderWindow)
	{
		std::cout << "Renderer::start(renderWindow)" << std::endl;

		_renderWindow = renderWindow;

		glfwMakeContextCurrent((GLFWwindow*)_renderWindow->getWindowPtr());

		if (glewInit() != GLEW_OK)
		{
			std::cerr << "Failed to initialize Glew." << std::endl;
			return false;
		}

		glGenVertexArrays(1, &_vertexArrayID);
		glBindVertexArray(_vertexArrayID);

		_model = glm::mat4(1.0f);
		_view = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		_projection = glm::ortho(0.0f, (float)_renderWindow->getWidth(), 0.0f, (float)_renderWindow->getHeight(), 0.0f, 1.0f);

		updateMVP();

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

	void Renderer::destroyVertexBuffer(unsigned int vertexBufferID)
	{
		glDeleteBuffers(1, &vertexBufferID);
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

	void Renderer::drawBuffer(PrimitiveType primitive, unsigned int vertexCount) const
	{
		glDrawArrays(primitive, 0, vertexCount);
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
}