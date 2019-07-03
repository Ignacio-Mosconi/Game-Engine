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
		Transform* parentTransform = _transform->getGameObject()->getParentTransform();
		
		glm::vec3 globalPos = _transform->getPosition();
		glm::vec3 localPos = _transform->getPosition();

		while (parentTransform)
		{
			globalPos += parentTransform->getPosition();
			parentTransform = parentTransform->getGameObject()->getParentTransform();
		}

		glm::vec3 center = globalPos - _transform->getForward();
		glm::vec3 upVector = _transform->getUp();		

		_renderer->updateView(globalPos, center, upVector);
	}
}