#include "Component.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "MeshRenderer.h"

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
			case ComponentID::SpriteRenderer:
				component = new SpriteRenderer();
				break;			
			case ComponentID::MeshRenderer:
				component = new MeshRenderer();
				break;
		}

		return component;
	}
}