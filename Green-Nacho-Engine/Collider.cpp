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
		destroyGeometry();
	}
	
	void Collider::destroyGeometry()
	{
		if (_geometry)
			delete _geometry;
	}
}