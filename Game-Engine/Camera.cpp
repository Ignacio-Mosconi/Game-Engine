#include "Camera.h"
#include "Renderer.h"

namespace gn
{
	Camera::Camera(Renderer* renderer, glm::vec3 position, glm::vec3 rotation, glm::vec3 forward, glm::vec3 up, glm::vec3 right) : 
	Entity(renderer, position, rotation, glm::vec3(1.0f, 1.0f, 1.0f)),
	_forward(forward), _up(up), _right(right)
	{
		updateRenderer();
	}

	Camera::~Camera()
	{

	}

	void Camera::updateRenderer()
	{
		_renderer->updateView(_position, _position - _forward, _up);
	}

	void Camera::setPosition(float x, float y, float z)
	{
		Entity::setPosition(x, y, z);
		
		updateRenderer();
	}

	void Camera::setRotation(float x, float y, float z)
	{
		float pitchAngle = x - _rotation.x;
		float yawAngle = y - _rotation.y;
		float rollAngle = z - _rotation.z;

		pitch(pitchAngle);
		yaw(yawAngle);
		roll(rollAngle);
		
		updateRenderer();
	}

	void Camera::translate(float x, float y, float z)
	{
		strafe(x);
		ascend(y);
		advance(z);

		updateRenderer();
	}

	void Camera::rotate(float x, float y, float z)
	{
		pitch(x);
		yaw(y);
		roll(z);

		updateRenderer();
	}

	void Camera::advance(const float distance)
	{
		_position -= _forward * distance;
		
		updateRenderer();
	}
	
	void Camera::strafe(const float distance)
	{
		_position += _right * distance;
		
		updateRenderer();
	}	
	
	void Camera::ascend(const float distance)
	{
		_position += _up * distance;
		
		updateRenderer();
	}

	void Camera::pitch(const float angle)
	{
		float pitch = -glm::radians(angle);
		
		Entity::rotate(angle, 0.0f, 0.0f);
		
		_forward = glm::normalize(_forward * glm::cos(pitch) + _up * glm::sin(pitch));
		_up = glm::normalize(glm::cross(_forward, _right));

		updateRenderer();
	}	
	
	void Camera::yaw(const float angle)
	{	
		float yaw = -glm::radians(angle);

		Entity::rotate(0.0f, angle, 0.0f);

		_forward = glm::normalize(_forward * glm::cos(yaw) + _right * glm::sin(yaw));
		_right = -glm::normalize(glm::cross(_forward, _up));

		updateRenderer();
	}	
	
	void Camera::roll(const float angle)
	{
		float roll = -glm::radians(angle);

		Entity::rotate(0.0f, 0.0f, angle);

		_right = glm::normalize(_right * glm::cos(roll) + _up * glm::sin(roll));
		_up = glm::normalize(glm::cross(_forward, _right));

		updateRenderer();
	}
}