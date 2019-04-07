#include "Camera.h"
#include "Renderer.h"

namespace gn
{
	Camera::Camera(Renderer* renderer)
	{
		_renderer->updateView(_position, _position - _forward, _up);
	}

	Camera::Camera(Renderer* renderer, glm::vec3 pos, glm::vec3 rot, glm::vec3 up, glm::vec3 forward, glm::vec3 right) : 
		_renderer(renderer), _position(pos), _rotation(rot), _up(up), _forward(forward), _right(right)
	{
		_renderer->updateView(_position, _position - _forward, _up);
	}

	void Camera::advance(const float distance)
	{
		_position -= _forward * distance;
		
		_renderer->updateView(_position, _position - _forward, _up);
	}
	
	void Camera::strafe(const float distance)
	{
		_position += _right * distance;
		
		_renderer->updateView(_position, _position - _forward, _up);
	}	
	
	void Camera::ascend(const float distance)
	{
		_position += _up * distance;
		
		_renderer->updateView(_position, _position - _forward, _up);
	}

	void Camera::pitch(const float angle)
	{
		_rotation.x += angle;
		
		float pitch = -glm::radians(angle);

		_forward = glm::normalize(_forward * glm::cos(pitch) + _up * glm::sin(pitch));
		_up = glm::normalize(glm::cross(_forward, _right));

		_renderer->updateView(_position, _position - _forward, _up);
	}	
	
	void Camera::yaw(const float angle)
	{
		_rotation.y += angle;
		
		float yaw = glm::radians(angle);

		_forward = glm::normalize(_forward * glm::cos(yaw) + _right * glm::sin(yaw));
		_right = glm::normalize(glm::cross(_forward, _up));

		_renderer->updateView(_position, _position - _forward, _up);
	}	
	
	void Camera::roll(const float angle)
	{
		_rotation.z += angle;

		float roll = glm::radians(angle);

		_right = glm::normalize(_right * glm::cos(roll) + _up * glm::sin(roll));
		_up = glm::normalize(glm::cross(_forward, _right));

		_renderer->updateView(_position, _position - _forward, _up);
	}
}