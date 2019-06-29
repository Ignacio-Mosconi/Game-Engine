#pragma once

#include "Exports.h"
#include "Component.h"

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

		void destroyGeometry();

		inline physx::PxGeometry* getGeometry() { return _geometry;  }
	};
}