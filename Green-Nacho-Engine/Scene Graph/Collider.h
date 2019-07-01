#pragma once

#include "Core/Exports.h"
#include "Scene Graph/Component.h"

namespace physx
{
	class PxGeometry;
}

namespace gn
{
	class ENGINE_DECL_SPEC Collider : public Component
	{
	protected:
		physx::PxGeometry* _geometry;
	
	public:
		Collider(ComponentID colliderID);
		virtual ~Collider();

		virtual void stop() override;

		void disposeGeometry();

		inline physx::PxGeometry* getGeometry() { return _geometry;  }
	};
}