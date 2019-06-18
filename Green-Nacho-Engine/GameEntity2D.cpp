#include "GameEntity2D.h"
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
	GameEntity2D::GameEntity2D(Renderer* renderer, const std::string& imagePath, const std::string& collisionLayer) :
	_sprite(createSprite(renderer, imagePath)), _material(NULL), _texture(NULL), _tilemap(NULL)
	{
		if (_sprite)
			_sprite->setPosition(0, 0, 0);
	
		float bbWidth = (float)(_sprite->getFrameWidth());
		float bbHeight = (float)(_sprite->getFrameHeight());

		createBoundingBox(bbWidth, bbHeight, false, 1.0f, collisionLayer);
	}

	GameEntity2D::GameEntity2D(Renderer* renderer, Tilemap* tilemap, const std::string& imagePath, const std::string& collisionLayer,
							float x, float y, int spriteRows, int spriteColumns, float frameWidth, float frameHeight, 
							bool isStatic, float mass) :
	_sprite(createSprite(renderer, imagePath, spriteRows, spriteColumns, frameWidth, frameHeight)),
	_material(NULL), _texture(NULL), _tilemap(tilemap)
	{
		if (_sprite)
			_sprite->setPosition(x, y, 0);

		float bbWidth = (float)(_sprite->getFrameWidth());
		float bbHeight = (float)(_sprite->getFrameHeight());

		createBoundingBox(bbWidth, bbHeight, isStatic, mass, collisionLayer);
	}

	GameEntity2D::~GameEntity2D()
	{
		_sprite->dispose();

		delete _sprite;
		delete _boundingBox;
	
		Texture::destroyTexture(_texture);
		Material::destroyMaterial(_material);
	}

	Sprite* GameEntity2D::createSprite(Renderer* renderer, const std::string& imagePath, int spriteRows, int spriteColumns, 
									float frameWidth, float frameHeight)
	{
		_material = Material::generateMaterial(TEXTURE_VERTEX_SHADER_PATH, TEXTURE_PIXEL_SHADER_PATH);
		_texture = Texture::generateTextureBMP(imagePath);
		_material->setTexture(_texture, "textureSampler");
	
		_sprite = new Sprite(renderer, _material, frameWidth, frameHeight, spriteRows, spriteColumns);
		if (frameWidth == -1)
			frameWidth = (float)_texture->getWidth();
		if (frameHeight == -1)
			frameHeight = (float)_texture->getHeight();
		_sprite->setAnimationFrame(0);

		return _sprite;
	}

	void GameEntity2D::createBoundingBox(float width, float height, bool isStatic, float mass, const std::string& collisionLayer)
	{
		_boundingBox = new BoundingBox(width, height, isStatic, mass);
		_boundingBox->attachToGameEntity(this);
		CollisionManager::getInstance()->registerBoundingBox(_boundingBox, collisionLayer);
	}

	void GameEntity2D::addAnimation(Animation* animation, const std::string& animName)
	{
		_animations[animName] = animation;
		animation->setSprite(_sprite);
	}

	Animation* GameEntity2D::getCurrentAnimation() const
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

	void GameEntity2D::setBoundingBoxDimensions(float width, float height)
	{
		_boundingBox->setWidth(width);
		_boundingBox->setHeight(height);
	}

	void GameEntity2D::move(float x, float y, float z)
	{
		_sprite->translate(x, y, z);

		float horOffset = _boundingBox->getWidth() / 2.0f;
		float verOffset = _boundingBox->getHeight() / 2.0f;
		float newPosX = _sprite->getPosition().x;
		float newPosY = _sprite->getPosition().y;
		int possibleHorCols = (int)glm::max(_boundingBox->getHeight() / Tile::height + 1.0f, 2.0f);
		int possibleVerCols = (int)glm::max(_boundingBox->getWidth() / Tile::width + 1.0f, 2.0f);
	
		if (x != 0.0f)
		{
			for (int i = -possibleHorCols / 2; i <= possibleHorCols / 2; i++)
			{
				if (x > 0.0f)
				{
					glm::vec2 rightTileCoord = _tilemap->worldToGrid(_sprite->getPosition().x + horOffset,
						_sprite->getPosition().y + (verOffset / (possibleHorCols / 2)) * i + Tile::height);

					TileType rightTileType = _tilemap->getTileType((unsigned int)rightTileCoord.x, (unsigned int)rightTileCoord.y);

					if (rightTileType == TileType::WALL)
					{
						newPosX = (_tilemap->gridToWorld((unsigned int)rightTileCoord.x, (unsigned int)rightTileCoord.y)).x - horOffset;
						break;
					}
				}
				else
				{
					glm::vec2 leftTileCoord = _tilemap->worldToGrid(_sprite->getPosition().x - horOffset, 
						_sprite->getPosition().y + (verOffset / (possibleHorCols / 2)) * i + Tile::height);
				
					TileType leftTileType = _tilemap->getTileType((unsigned int)leftTileCoord.x, (unsigned int)leftTileCoord.y);

					if (leftTileType == TileType::WALL)
					{
						newPosX = (_tilemap->gridToWorld((unsigned int)leftTileCoord.x, (unsigned int)leftTileCoord.y)).x + horOffset + Tile::width;
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
				
					TileType upperTileType = _tilemap->getTileType((unsigned int)upperTileCoord.x, (unsigned int)upperTileCoord.y);

					if (upperTileType == TileType::WALL)
					{
						newPosY = (_tilemap->gridToWorld((unsigned int)upperTileCoord.x, (unsigned int)upperTileCoord.y)).y - verOffset - _tilemap->getLastRowOffset();
						break;
					}
				}
				else
				{
					glm::vec2 lowerTileCoord = _tilemap->worldToGrid(_sprite->getPosition().x + (horOffset / (possibleVerCols / 2)) * i,
						_sprite->getPosition().y - verOffset);
				
					TileType lowerTileType = _tilemap->getTileType((unsigned int)lowerTileCoord.x, (unsigned int)lowerTileCoord.y);

					if (lowerTileType == TileType::WALL)
					{
						newPosY = (_tilemap->gridToWorld((unsigned int)lowerTileCoord.x, (unsigned int)lowerTileCoord.y)).y + verOffset;
						break;
					}
				}
			}
		}

		if (newPosX != _sprite->getPosition().x || newPosY != _sprite->getPosition().y)
			_sprite->setPosition(newPosX, newPosY, _sprite->getPosition().z);
	}

	void GameEntity2D::update(float deltaTime)
	{
		std::map<std::string, Animation*>::iterator mapIt;
	
		for (mapIt = _animations.begin(); mapIt != _animations.end(); mapIt++)
			mapIt->second->update(deltaTime);
	}

	void GameEntity2D::draw() const
	{
		_sprite->draw();
	}
}