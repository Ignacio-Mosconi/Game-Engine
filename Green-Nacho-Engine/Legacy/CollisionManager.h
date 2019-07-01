#pragma once
#pragma warning(disable: 4251)

#include <map>
#include <string>
#include <vector>
#include "Core/Exports.h"

namespace gn
{
	namespace legacy
	{
		class BoundingBox;
/*
		The "CollisionManager" is a singleton class that is used to detect collisons
		between entities; their bounding boxes must first be registered inside this manager.
*/
		class ENGINE_DECL_SPEC CollisionManager
		{
		private:
			static CollisionManager* _instance;

			std::map<std::string, std::vector<BoundingBox*>> _collisionLayers;

			CollisionManager();
			~CollisionManager();

		public:
			static CollisionManager* getInstance();
			static void deleteInstance();

			void registerBoundingBox(BoundingBox* box, const std::string& layer);
			bool deregisterBoundingBox(BoundingBox* box);

			void update();
		};
	}
}