#include "GameEntity.h"
#include "Sprite.h"
#include "BoundingBox.h"
#include "Renderer.h"
#include "Material.h"
#include "Texture.h"
#include "CollisionManager.h"
#include "Animation.h"
#include "Tilemap.h"

GameEntity::GameEntity(Renderer* renderer, const string& imagePath, const string& collisionLayer) :
_sprite(createSprite(renderer, imagePath)), _material(NULL), _texture(NULL), _tilemap(NULL)
{
	cout << "GameEntity::GameEntity(renderer, imagePath, collisionLayer)" << endl;

	if (_sprite)
		_sprite->setPosition(0, 0, 0);
	
	float bbWidth = (float)(_sprite->getFrameWidth());
	float bbHeight = (float)(_sprite->getFrameHeight());

	createBoundingBox(bbWidth, bbHeight, false, 1.0f, collisionLayer);
}

GameEntity::GameEntity(Renderer* renderer, Tilemap* tilemap, const string& imagePath, const string& collisionLayer,
						float x, float y, int spriteRows, int spriteColumns, int frameWidth, int frameHeight, 
						bool isStatic, float mass) :
_sprite(createSprite(renderer, imagePath, spriteRows, spriteColumns, frameWidth, frameHeight)),
_material(NULL), _texture(NULL), _tilemap(tilemap)
{
	cout << "GameEntity::GameEntity(renderer, imagePath, collisionLayer, x, y)" << endl;

	if (_sprite)
		_sprite->setPosition(x, y, 0);

	float bbWidth = (float)(_sprite->getFrameWidth());
	float bbHeight = (float)(_sprite->getFrameHeight());

	createBoundingBox(bbWidth, bbHeight, isStatic, mass, collisionLayer);
}

GameEntity::~GameEntity()
{
	cout << "GameEntity::~GameEntity()" << endl;

	_sprite->dispose();

	delete _sprite;
	delete _boundingBox;
	
	Texture::destroyTexture(_texture);
	Material::destroyMaterial(_material);
}

Sprite* GameEntity::createSprite(Renderer* renderer, const string& imagePath, int spriteRows, int spriteColumns, 
								int frameWidth, int frameHeight)
{
	cout << "GameEntity::createSprite(renderer, imagePath)" << endl;

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

void GameEntity::createBoundingBox(float width, float height, bool isStatic, float mass, const string& collisionLayer)
{
	_boundingBox = new BoundingBox(width, height, isStatic, mass);
	_boundingBox->attachToEntity(_sprite);
	CollisionManager::getInstance()->registerBoundingBox(_boundingBox, collisionLayer);
}

void GameEntity::addAnimation(Animation* animation, const string& animName)
{
	_animations[animName] = animation;
	animation->setSprite(_sprite);
}

void GameEntity::setBoundingBoxDimensions(float width, float height)
{
	cout << "GameEntity::setBoundingBoxDimensions(width, height)" << endl;

	_boundingBox->setWidth(width);
	_boundingBox->setHeight(height);
}

void GameEntity::move(float x, float y, float z)
{
	cout << "GameEntity::move(x, y, z)" << endl;

	_sprite->translate(x, y, z);

	float horOffset = _boundingBox->getWidth() / 2.0f;
	float verOffset = _boundingBox->getHeight() / 2.0f;
	float newPosX = _sprite->getPosition().x;
	float newPosY = _sprite->getPosition().y;
	int possibleHorCols = glm::max(_boundingBox->getHeight() / Tile::tileHeight, 2.0f);
	int possibleVerCols = glm::max(_boundingBox->getWidth() / Tile::tileWidth, 2.0f);
	
	if (x != 0.0f)
	{
		for (int i = -possibleHorCols / 2; i < possibleHorCols / 2; i++)
		{
			if (x > 0.0f)
			{
				vec2 rightTileCoord = _tilemap->worldToGrid(_sprite->getPosition().x + horOffset, 
															_sprite->getPosition().y + (verOffset / (float)possibleHorCols / 2.0f) * i);
				TileType rightTileType = _tilemap->getTileType(rightTileCoord.x, rightTileCoord.y);

				if (rightTileType == Wall)
				{
					newPosX = (_tilemap->gridToWorld(rightTileCoord.x, rightTileCoord.y)).x - horOffset;
					break;
				}
			}
			else
			{
				vec2 leftTileCoord = _tilemap->worldToGrid(_sprite->getPosition().x - horOffset, 
															_sprite->getPosition().y + (verOffset / (float)possibleHorCols / 2.0f) * i);
				TileType leftTileType = _tilemap->getTileType(leftTileCoord.x, leftTileCoord.y);

				if (leftTileType == Wall)
				{
					newPosX = (_tilemap->gridToWorld(leftTileCoord.x, leftTileCoord.y)).x + horOffset + Tile::tileWidth;
					break;
				}
			}
		}
	}
	
	if (y != 0.0f)
	{
		for (int i = -possibleVerCols / 2; i < possibleVerCols / 2; i++)
		{
			if (y > 0.0f)
			{
				vec2 upperTileCoord = _tilemap->worldToGrid(_sprite->getPosition().x + (horOffset / (float)possibleVerCols / 2.0f) * i, 
															_sprite->getPosition().y + verOffset);
				TileType upperTileType = _tilemap->getTileType(upperTileCoord.x, upperTileCoord.y);

				if (upperTileType == Wall)
				{
					newPosY = (_tilemap->gridToWorld(upperTileCoord.x, upperTileCoord.y)).y - verOffset - Tile::tileHeight;
					break;
				}
			}
			else
			{
				vec2 lowerTileCoord = _tilemap->worldToGrid(_sprite->getPosition().x + (horOffset / (float)possibleVerCols / 2.0f) * i,
															_sprite->getPosition().y - verOffset);
				TileType lowerTileType = _tilemap->getTileType(lowerTileCoord.x, lowerTileCoord.y);

				if (lowerTileType == Wall)
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
	cout << "GameEntity::update()" << endl;

	map<string, Animation*>::iterator mapIt;
	for (mapIt = _animations.begin(); mapIt != _animations.end(); mapIt++)
		mapIt->second->update(deltaTime);
}

void GameEntity::draw() const
{
	cout << "GameEntity::draw()" << endl;

	_sprite->draw();
}