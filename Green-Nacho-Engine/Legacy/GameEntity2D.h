#pragma once
#pragma warning(disable: 4251)

#include <map>
#include <string>
#include "Core/Material.h"
#include "Core/Exports.h"
#include "Core/EngineConstants.h"

namespace gn
{
	class Renderer;
	class Material;
	class Texture;

	namespace legacy
	{
		class Sprite;
		class BoundingBox;
		class Animation;
		class Tilemap;
/*
		A complex class that is meant to be used as a base for all the characters and/or interactables of a game;
		they contain a "Sprite" (for rendering) and a "BoundingBox" (for collision detection), and they also have
		the possibility to include animations.
*/
		class ENGINE_DECL_SPEC GameEntity2D
		{
		private:
			Sprite* _sprite;
			BoundingBox* _boundingBox;

			mutable std::map<std::string, Animation*> _animations;

			Material* _material;
			Texture* _texture;

			Tilemap* _tilemap;

			Sprite* createSprite(Renderer* renderer, const std::string& imagePath, int spriteRows = 1, int spriteColumns = 1,
				float frameWidth = -1, float frameHeight = -1);
			void createBoundingBox(float width, float height, bool isStatic, float mass, const std::string& collisionLayer);

		public:
			GameEntity2D(Renderer* renderer, const std::string& imagePath, const std::string& collisionLayer);
			GameEntity2D(Renderer* renderer, Tilemap* tilemap, const std::string& imagePath, const std::string& collisionLayer,
				float x, float y, int spriteRows, int spriteColumns, float frameWidth, float frameHeight,
				bool isStatic = false, float mass = 1);
			virtual ~GameEntity2D();

			void setBoundingBoxDimensions(float width, float height);

			void addAnimation(Animation* animation, const std::string& animName);

			void move(float x, float y, float z = 0.0f);

			virtual void update(float deltaTime);
			virtual void draw() const;

			inline Animation* getCurrentAnimation() const;
			inline Sprite* getSprite() const { return _sprite; }
			inline BoundingBox* getBoundingBox() const { return _boundingBox; }
		};
	}
}