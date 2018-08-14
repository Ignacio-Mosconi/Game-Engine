#include "Renderer.h"

Renderer::Renderer()
{
	cout << "Renderer::Renderer()" << endl;
}

Renderer::~Renderer()
{
	cout << "Renderer::~Renderer()" << endl;
}

bool Renderer::start()
{
	cout << "Renderer::start()" << endl;

	return true;
}

bool Renderer::stop()
{
	cout << "Renderer::stop()" << endl;

	return true;
}
