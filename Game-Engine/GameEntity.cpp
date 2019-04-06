#include "GameEntity.h"
#include "Sprite.h"
#include "BoundingBox.h"
#include "Renderer.h"
#include "Material.h"
#include "Texture.h"
#include "CollisionManager.h"
#include "Animation.h"
#include "Tilemap.h"

namespace gn
{
	GameEntity::GameEntity(Renderer* renderer, const std::string& imagePath, const std::string& collisionLayer) :
	_sprite(createSprite(renderer, imagePath)), _material(NULL), _texture(NULL), _tilemap(NULL)
	{
		std::cout << "GameEntity::GameEntity(renderer, imagePath, collisionLayer)" << std::endl;

		if (_sprite)
			_sprite->setPosition(0, 0, 0);
	
		float bbWidth = (float)(_sprite->getFrameWidth());
		float bbHeight = (float)(_sprite->getFrameHeight());

		createBoundingBox(bbWidth, bbHeight, false, 1.0f, collisionLayer);
	}

	GameEntity::GameEntity(Renderer* renderer, Tilemap* tilemap, const std::string& imagePath, const std::string& collisionLayer,
							float x, float y, int spriteRows, int spriteColumns, int frameWidth, int frameHeight, 
							bool isStatic, float mass) :
	_sprite(createSprite(renderer, imagePath, spriteRows, spriteColumns, frameWidth, frameHeight)),
	_material(NULL), _texture(NULL), _tilemap(tilemap)
	{
		std::cout << "GameEntity::GameEntity(renderer, imagePath, collisionLayer, x, y)" << std::endl;

		if (_sprite)
			_sprite->setPosition(x, y, 0);

		float bbWidth = (float)(_sprite->getFrameWidth());
		float bbHeight = (float)(_sprite->getFrameHeight());

		createBoundingBox(bbWidth, bbHeight, isStatic, mass, collisionLayer);
	}

	GameEntity::~GameEntity()
	{
		std::cout << "GameEntity::~GameEntity()" << std::endl;

		_sprite->dispose();

		delete _sprite;
		delete _boundingBox;
	
		Texture::destroyTexture(_texture);
		Material::destroyMaterial(_material);
	}

	Sprite* GameEntity::createSprite(Renderer* renderer, const std::string& imagePath, int spriteRows, int spriteColumns, 
									int frameWidth, int frameHeight)
	{
		_material = Material::generateMaterial(TEXTURE_VERTEX_SHADER_PATH, TEXTURE_PIXEL_SHADER_PATH);
		_texture = Texture::generateTextureBMP(imagePath);
		_material->setTexture(_texture, "textureSampler");
	
		_sprite = new Sprite(renderer, _material);
		if (frameWidth == -1)
			frameWidth = _texture->getWidth();
		if (frameHeight == -1)
			frameHeight = _texture->getHeight();
		_sprite->create(3, NULL, frameWidth, frameHeight);
		_sprite->setFramesInfo(spriteRows, spriteColumns, frameWidth, frameHeight);
		_sprite->setAnimationFrame(0);

		return _sprite;
	}

	void GameEntity::createBoundingBox(float width, float height, bool isStatic, float mass, const std::string& collisionLayer)
	{
		_boundingBox = new BoundingBox(width, height, isStatic, mass);
		_boundingBox->attachToGameEntity(this);
		CollisionManager::getInstance()->registerBoundingBox(_boundingBox, collisionLayer);
	}

	void GameEntity::addAnimation(Animation* animation, const std::string& animName)
	{
		_animations[animName] = animation;
		animation->setSprite(_sprite);
	}

	Animation* GameEntity::getCurrentAnimation() const
	{
		std::map<std::string, Animation*>::iterator mapIt;

		Animation* anim = NULL;

		for (mapIt = _animations.begin(); mapIt != _animations.end(); mapIt++)
			if (mapIt->second->isPlaying())
			{
				anim = mapIt->second;
				break;
			}

		return anim;
	}

	void GameEntity::setBoundingBoxDimensions(float width, float height)
	{
		_boundingBox->setWidth(width);
		_boundingBox->setHeight(height);
	}

	void GameEntity::move(float x, float y, float z)
	{
		_sprite->translate(x, y, z);

		float horOffset = _boundingBox->getWidth() / 2.0f;
		float verOffset = _boundingBox->getHeight() / 2.0f;
		float newPosX = _sprite->getPosition().x;
		float newPosY = _sprite->getPosition().y;
		int possibleHorCols = glm::max(_boundingBox->getHeight() / Tile::height + 1.0f, 2.0f);
		int possibleVerCols = glm::max(_boundingBox->getWidth() / Tile::width + 1.0f, 2.0f);
	
		if (x != 0.0f)
		{
			for (int i = -possibleHorCols / 2; i <= possibleHorCols / 2; i++)
			{
				if (x > 0.0f)
				{
					glm::vec2 rightTileCoord = _tilemap->worldToGrid(_sprite->getPosition().x + horOffset,
						_sprite->getPosition().y + (verOffset / (possibleHorCols / 2)) * i + Tile::height);

					TileType rightTileType = _tilemap->getTileType(rightTileCoord.x, rightTileCoord.y);

					if (rightTileType == TileType::WALL)
					{
						newPosX = (_tilemap->gridToWorld(rightTileCoord.x, rightTileCoord.y)).x - horOffset;
						break;
					}
				}
				else
				{
					glm::vec2 leftTileCoord = _tilemap->worldToGrid(_sprite->getPosition().x - horOffset, 
						_sprite->getPosition().y + (verOffset / (possibleHorCols / 2)) * i + Tile::height);
				
					TileType leftTileType = _tilemap->getTileType(leftTileCoord.x, leftTileCoord.y);

					if (leftTileType == TileType::WALL)
					{
						newPosX = (_tilemap->gridToWorld(leftTileCoord.x, leftTileCoord.y)).x + horOffset + Tile::width;
						break;
					}
				}
			}
		}
	
		if (y != 0.0f)
		{
			for (int i = -possibleVerCols / 2; i <= possibleVerCols / 2; i++)
			{
				if (y > 0.0f)
				{
					glm::vec2 upperTileCoord = _tilemap->worldToGrid(_sprite->getPosition().x + (horOffset / (possibleVerCols / 2)) * i,
						_sprite->getPosition().y + verOffset);
				
					TileType upperTileType = _tilemap->getTileType(upperTileCoord.x, upperTileCoord.y);

					if (upperTileType == TileType::WALL)
					{
						newPosY = (_tilemap->gridToWorld(upperTileCoord.x, upperTileCoord.y)).y - verOffset - _tilemap->getLastRowOffset();
						break;
					}
				}
				else
				{
					glm::vec2 lowerTileCoord = _tilemap->worldToGrid(_sprite->getPosition().x + (horOffset / (possibleVerCols / 2)) * i,
						_sprite->getPosition().y - verOffset);
				
					TileType lowerTileType = _tilemap->getTileType(lowerTileCoord.x, lowerTileCoord.y);

					if (lowerTileType == TileType::WALL)
					{
						newPosY = (_tilemap->gridToWorld(lowerTileCoord.x, lowerTileCoord.y)).y + verOffset;
						break;
					}
				}
			}
		}

		if (newPosX != _sprite->getPosition().x || newPosY != _sprite->getPosition().y)
			_sprite->setPosition(newPosX, newPosY, _sprite->getPosition().z);
	}

	void GameEntity::update(float deltaTime)
	{
		std::map<std::string, Animation*>::iterator mapIt;
	
		for (mapIt = _animations.begin(); mapIt != _animations.end(); mapIt++)
			mapIt->second->update(deltaTime);
	}

	void GameEntity::draw() const
	{
		_sprite->draw();
	}
}