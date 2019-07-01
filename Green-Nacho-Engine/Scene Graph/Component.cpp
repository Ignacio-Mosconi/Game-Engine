#include "Scene Graph/Component.h"
#include "Scene Graph/Transform.h"
#include "Scene Graph/Camera.h"
#include "Scene Graph/SpriteRenderer.h"
#include "Scene Graph/MeshRenderer.h"
#include "Scene Graph/CapsuleCollider.h"
#include "Scene Graph/RigidBody.h"

namespace gn
{
	Component::Component(const ComponentID id) : _id(id)
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

	void Component::update()
	{
	}

	void Component::draw() const
	{
	}

	Component* Component::generateComponent(ComponentID componentID)
	{
		Component* component = NULL;

		switch (componentID)
		{
			case ComponentID::Transform:
				component = new Transform();
				break;
			case ComponentID::Camera:
				component = new Camera();
				break;
			case ComponentID::SpriteRenderer:
				component = new SpriteRenderer();
				break;			
			case ComponentID::MeshRenderer:
				component = new MeshRenderer();
				break;
			case ComponentID::CapsuleCollider:
				component = new CapsuleCollider();
				break;
			case ComponentID::RigidBody:
				component = new RigidBody();
				break;
		}

		return component;
	}
}