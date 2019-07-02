#include "Scene Graph/Camera.h"
#include "Core/Renderer.h"
#include "Scene Graph/GameObject.h"
#include "Scene Graph/Transform.h"

namespace gn
{
	Camera::Camera(GameObject* gameObject) : Component(ComponentID::Camera, gameObject),
		_renderer(NULL), _transform(NULL)
	{

	}

	Camera::~Camera()
	{

	}

	void Camera::start()
	{
		_renderer = _gameObject->getRenderer();
		_transform = _gameObject->getTransform();
	}	
	
	void Camera::stop()
	{
		if (_renderer)
			_renderer = NULL;
		if (_transform)
			_transform = NULL;
	}

	void Camera::update(float deltaTime)
	{
		std::stack<glm::vec3> stackedPositions;
		Transform* transform = _transform;
		
		glm::vec3 position(0.0f, 0.0f, 0.0f);	
		stackedPositions.push(_transform->getPosition());

		do
		{
			transform = transform->getGameObject()->getParentTransform();
			if (transform)
				stackedPositions.push(transform->getPosition());
		} while (transform);

		while (!stackedPositions.empty())
		{
			position += stackedPositions.top();
			stackedPositions.pop();
		}

		glm::vec3 center = position - _transform->getForward();
		glm::vec3 up = _transform->getUp();

		_renderer->updateView(position, center, up);
	}
}