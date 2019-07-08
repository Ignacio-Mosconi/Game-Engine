#include "Scene Graph/Camera.h"
#include "Core/Renderer.h"
#include "Core/Window.h"
#include "Scene Graph/GameObject.h"
#include "Scene Graph/Transform.h"
#include "Scene Graph/BoundingBox.h"

namespace gn
{
	Camera::Camera(GameObject* gameObject) : Component(ComponentID::CAMERA, gameObject),
		_renderer(NULL), _transform(NULL)
	{

	}

	Camera::~Camera()
	{

	}

	glm::vec4 Camera::generatePlane(glm::vec3 normal, glm::vec3 point)
	{
		glm::vec4 plane;

		plane.x = normal.x;
		plane.y = normal.y;
		plane.z = normal.z;
		plane.w = -glm::dot(normal, point);

		return plane;
	}

	void Camera::start()
	{
		_renderer = _gameObject->getRenderer();
		_transform = _gameObject->getTransform();

		float windowWidth = (float)_renderer->getRenderWindow()->getWidth();
		float windowHeight = (float)_renderer->getRenderWindow()->getHeight();
		
		updateFrustumProperties(45.0f, windowWidth / windowHeight, 0.1f, 1000.0f);
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
		glm::vec3 globalPos = _transform->getPosition();
		
		Transform* parentTransform = _transform->getGameObject()->getParentTransform();

		while (parentTransform)
		{
			globalPos += parentTransform->getPosition();
			parentTransform = parentTransform->getGameObject()->getParentTransform();
		}

		if (_globalPosition != globalPos || _viewDirection != _transform->getForward())
		{
			_globalPosition = globalPos;
			_viewDirection = _transform->getForward();

			glm::vec3 center = _globalPosition + _viewDirection;
			glm::vec3 upVector = _transform->getUp();		

			updateFrustum();
			_renderer->updateView(_globalPosition, center, upVector);
		}
	}

	void Camera::updateFrustum()
	{
		glm::vec3 right = _transform->getRight();
		glm::vec3 up = glm::normalize(glm::cross(_viewDirection, right));

		glm::vec3 nearCenter = _globalPosition + _viewDirection * _nearDistance;
		glm::vec3 farCenter = _globalPosition + _viewDirection * _farDistance;

		glm::vec3 leftPlaneVec = (nearCenter - right * _nearWidth * 0.5f) - _globalPosition;
		glm::vec3 rightPlaneVec = (nearCenter + right * _nearWidth * 0.5f) - _globalPosition;
		glm::vec3 topPlaneVec = (nearCenter + up * _nearHeight * 0.5f) - _globalPosition;
		glm::vec3 bottomPlaneVec = (nearCenter - up * _nearHeight * 0.5f) - _globalPosition;

		glm::vec3 normalLeft = -glm::normalize(glm::cross(leftPlaneVec, up));
		glm::vec3 normalRight = glm::normalize(glm::cross(rightPlaneVec, up));
		glm::vec3 normalTop = -glm::normalize(glm::cross(topPlaneVec, right));
		glm::vec3 normalBottom = glm::normalize(glm::cross(bottomPlaneVec, right));

		_frustumPlanes[(int)FrustumPlane::NEAR] = generatePlane(_viewDirection, nearCenter);
		_frustumPlanes[(int)FrustumPlane::FAR] = generatePlane(-_viewDirection, farCenter);
		_frustumPlanes[(int)FrustumPlane::LEFT] = generatePlane(normalLeft, _globalPosition);
		_frustumPlanes[(int)FrustumPlane::RIGHT] = generatePlane(normalRight, _globalPosition);
		_frustumPlanes[(int)FrustumPlane::TOP] = generatePlane(normalTop, _globalPosition);
		_frustumPlanes[(int)FrustumPlane::BOTTOM] = generatePlane(normalBottom, _globalPosition);
	}

	void Camera::updateFrustumProperties(float fieldOfView, float aspectRatio, float nearDistance, float farDistance)
	{
		_nearDistance = nearDistance;
		_farDistance = farDistance;
		_fovTangent = glm::tan(glm::radians(fieldOfView));
		_nearHeight = nearDistance * _fovTangent;
		_nearWidth = _nearHeight * aspectRatio;
		_farHeight = farDistance * _fovTangent;
		_farWidth = _farHeight * aspectRatio;

		updateFrustum();
		_renderer->changePerspProjection(fieldOfView, aspectRatio, nearDistance, farDistance);
	}

	bool Camera::isInsideFrustum(BoundingBox* boundingBox)
	{
		bool isInsideFrustum = true;
		bool allOutsideCurrentPlane = false;

		for (int i = 0; i < (int)FrustumPlane::COUNT; i++)
		{
			allOutsideCurrentPlane = false;

			for (int j = 0; j < CUBE_VERTICES; j++)
			{
				glm::vec3 vertexPosition = boundingBox->getVertexPosition(j);
				glm::vec3 planeNormal = glm::vec3(_frustumPlanes[i]);

				float dist = glm::dot(planeNormal, vertexPosition) + _frustumPlanes[i].w;

				if (dist > 0.0f)
					break;
				if (j == CUBE_VERTICES - 1)
					allOutsideCurrentPlane = true;
			}

			if (allOutsideCurrentPlane)
			{
				isInsideFrustum = false;
				break;
			}
		}

		return isInsideFrustum;
	}
}