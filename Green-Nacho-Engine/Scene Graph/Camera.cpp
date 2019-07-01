#include "Scene Graph/Camera.h"
#include "Core/Renderer.h"
#include "Scene Graph/Transform.h"

namespace gn
{
	Camera::Camera() : Component(ComponentID::Camera),
		_renderer(NULL), _transform(NULL)
	{

	}

	Camera::~Camera()
	{

	}

	void Camera::update(float deltaTime)
	{
		glm::vec3 position = _transform->getPosition();
		glm::vec3 center = position - _transform->getForward();
		glm::vec3 up = _transform->getUp();

		_renderer->updateView(position, center, up);
	}	
	
	void Camera::stop()
	{
		deactivate();
	}

	void Camera::activate(Renderer* renderer, Transform* transform)
	{
		_renderer = renderer;
		_transform = transform;
	}

	void Camera::deactivate()
	{
		if (_renderer)
			_renderer = NULL;
		if (_transform)
			_transform = NULL;
	}
}