#include <PxPhysicsAPI.h>
#include "Scene Graph/Collider.h"

namespace gn
{
	Collider::Collider(ComponentID colliderID, GameObject* gameObject) : Component(colliderID, gameObject),
		_geometry(NULL)
	{

	}
	
	Collider::~Collider()
	{

	}	

	void Collider::stop()
	{
		disposeGeometry();
	}
	
	void Collider::disposeGeometry()
	{
		if (_geometry)
			delete _geometry;
	}
}