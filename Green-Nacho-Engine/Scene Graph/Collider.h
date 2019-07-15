#pragma once

#include "Core/Exports.h"
#include "Scene Graph/Component.h"

namespace physx
{
	class PxGeometry;
}

namespace gn
{
	class BoundingBox;

	class ENGINE_DECL_SPEC Collider : public Component
	{
	protected:
		physx::PxGeometry* _geometry;
	
	public:
		Collider(ComponentID colliderID, GameObject* gameObject);
		virtual ~Collider();

		virtual void stop() override;

		virtual void createGeometry(BoundingBox* boundingBox) = 0;
		void disposeGeometry();

		inline physx::PxGeometry* getGeometry() { return _geometry;  }
	};
}