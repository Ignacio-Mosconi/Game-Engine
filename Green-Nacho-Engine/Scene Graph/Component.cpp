#include "Scene Graph/Component.h"
#include "Scene Graph/GameObject.h"
#include "Scene Graph/Transform.h"
#include "Scene Graph/Camera.h"
#include "Scene Graph/BoundingBox.h"
#include "Scene Graph/SpriteRenderer.h"
#include "Scene Graph/MeshRenderer.h"
#include "Scene Graph/BoxCollider.h"
#include "Scene Graph/CapsuleCollider.h"
#include "Scene Graph/RigidBody.h"
#include "Scene Graph/NavigationController.h"
#include "Scene Graph/ThirdPersonCameraController.h"
#include "Scene Graph/Terrain.h"

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
			case ComponentID::TRANSFORM:
				component = new Transform(gameObject);
				break;
			case ComponentID::CAMERA:
				component = new Camera(gameObject);
				break;			
			case ComponentID::BOUNDING_BOX:
				component = new BoundingBox(gameObject);
				break;
			case ComponentID::SPRITE_RENDERER:
				component = new SpriteRenderer(gameObject);
				break;			
			case ComponentID::MESH_RENDERER:
				component = new MeshRenderer(gameObject);
				break;
			case ComponentID::BOX_COLLIDER:
				component = new BoxCollider(gameObject);
				break;			
			case ComponentID::CAPSULE_COLLIDER:
				component = new CapsuleCollider(gameObject);
				break;
			case ComponentID::RIGID_BODY:
				component = new RigidBody(gameObject);
				break;
			case ComponentID::NAVIGATION_CONTROLLER:
				component = new NavigationController(gameObject);
			break;
			case ComponentID::THIRD_PERSON_CAMERA_CONTROLLER:
				component = new ThirdPersonCameraController(gameObject);
				break;			
			case ComponentID::TERRAIN:
				component = new Terrain(gameObject);
				break;
		}

		return component;
	}
}