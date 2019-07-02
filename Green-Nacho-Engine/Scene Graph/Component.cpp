#include "Scene Graph/Component.h"
#include "Scene Graph/GameObject.h"
#include "Scene Graph/Transform.h"
#include "Scene Graph/Camera.h"
#include "Scene Graph/SpriteRenderer.h"
#include "Scene Graph/MeshRenderer.h"
#include "Scene Graph/CapsuleCollider.h"
#include "Scene Graph/RigidBody.h"
#include "Scene Graph/NavigationController.h"

namespace gn
{
	Component::Component(const ComponentID id, GameObject* gameObject) : _id(id), _gameObject(gameObject)
	{
	}

	Component::~Component()
	{
	}

	void Component::start()
	{
	}

	void Component::stop()
	{
	}

	void Component::update(float deltaTime)
	{
	}

	void Component::draw() const
	{
	}

	Component* Component::generateComponent(ComponentID componentID, GameObject* gameObject)
	{
		Component* component = NULL;

		switch (componentID)
		{
			case ComponentID::Transform:
				component = new Transform(gameObject);
				break;
			case ComponentID::Camera:
				component = new Camera(gameObject);
				break;
			case ComponentID::SpriteRenderer:
				component = new SpriteRenderer(gameObject);
				break;			
			case ComponentID::MeshRenderer:
				component = new MeshRenderer(gameObject);
				break;
			case ComponentID::CapsuleCollider:
				component = new CapsuleCollider(gameObject);
				break;
			case ComponentID::RigidBody:
				component = new RigidBody(gameObject);
				break;
			case ComponentID::NavigationController:
				component = new NavigationController(gameObject);
				break;
		}

		return component;
	}
}