#include "Camera.h"
#include "Renderer.h"

namespace gn
{
	Camera::Camera(Renderer* renderer)
	{

	}
	Camera::Camera(Renderer* renderer, glm::vec3 pos, glm::vec3 rot, glm::vec3 up, glm::vec3 forward, glm::vec3 right) : 
		_renderer(renderer), _position(pos), _rotation(rot), _up(up), _forward(forward), _right(right)
	{

	}

	void Camera::move(CameraMovementType movementType, float distance)
	{
		switch (movementType)
		{
			case CameraMovementType::WALK:
				_position += _forward * distance;
				break;			
			case CameraMovementType::STRAFE:
				_position += _right * distance;
				break;			
			case CameraMovementType::VERTICAL:
				_position += _up * distance;
				break;
		}

		_renderer->updateView(_position, _position + _forward, _up);
	}

	void Camera::rotate(CameraRotationType rotationType, float degrees)
	{

	}
}