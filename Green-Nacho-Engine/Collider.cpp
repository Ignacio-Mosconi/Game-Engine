#include "Collider.h"

namespace gn
{
	Collider::Collider(ComponentID colliderID) : Component(colliderID),
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