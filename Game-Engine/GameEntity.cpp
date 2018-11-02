#include "GameEntity.h"
#include "Sprite.h"
#include "BoundingBox.h"
#include "Renderer.h"
#include "Material.h"
#include "Texture.h"
#include "CollisionManager.h"

Material* GameEntity::_textureMaterial = NULL;

GameEntity::GameEntity(Renderer* renderer, string& imagePath, string& collisionLayer) :
_sprite(createSprite(renderer, imagePath)), _texture(NULL)
{
	cout << "GameEntity::GameEntity(renderer, imagePath, collisionLayer)" << endl;

	if (_sprite)
	{
		_sprite->setPosition(0, 0, 0);
		_sprite->setScale(130, 130, 130);
	}
	
	float bbWidth = (float)(_sprite->getFrameWidth());
	float bbHeight = (float)(_sprite->getFrameHeight());

	_boundingBox = new BoundingBox(bbWidth, bbHeight);
	_boundingBox->attachToEntity(_sprite);
	CollisionManager::getInstance()->registerBoundingBox(_boundingBox, collisionLayer);
}

GameEntity::GameEntity(Renderer* renderer, string& imagePath, string& collisionLayer, float x, float y,
						int spriteRows, int spriteColumns, int frameWidth, int frameHeight, bool isStatic, float mass) :
_sprite(createSprite(renderer, imagePath, spriteRows, spriteColumns, frameWidth, frameHeight))
{
	cout << "GameEntity::GameEntity(renderer, imagePath, collisionLayer, x, y)" << endl;

	if (_sprite)
	{
		_sprite->setPosition(x, y, 0);
		_sprite->setScale(130, 130, 130);
	}

	float bbWidth = (float)(_sprite->getFrameWidth());
	float bbHeight = (float)(_sprite->getFrameHeight());

	_boundingBox = new BoundingBox(bbWidth, bbHeight, isStatic, mass);
	_boundingBox->attachToEntity(_sprite);
	CollisionManager::getInstance()->registerBoundingBox(_boundingBox, collisionLayer);
}

GameEntity::~GameEntity()
{
	cout << "GameEntity::~GameEntity()" << endl;

	delete _sprite;
	delete _boundingBox;
	if (_textureMaterial)
	{
		Material::destroyMaterial(_textureMaterial);
		_textureMaterial = NULL;
	}
	if (_texture)
	{
		Texture::destroyTexture(_texture);
		_texture = NULL;
	}
}

Sprite* GameEntity::createSprite(Renderer* renderer, string& imagePath, int spriteRows, int spriteColumns, 
								int frameWidth, int frameHeight)
{
	cout << "GameEntity::createSprite(renderer, imagePath)" << endl;

	_texture = Texture::generateTextureBMP(imagePath);
	getTextureMaterial()->setTexture(_texture, "textureSampler");
	_sprite = new Sprite(renderer, getTextureMaterial());
	_sprite->create(3);
	if (frameWidth == -1)
		frameWidth = _texture->getWidth();
	if (frameHeight == -1)
		frameHeight = _texture->getHeight();
	_sprite->setFramesInfo(spriteRows, spriteColumns, frameWidth, frameHeight);
	_sprite->setAnimationFrame(0);

	return _sprite;
}

void GameEntity::setBoundingBoxDimensions(float width, float height)
{
	cout << "GameEntity::setBoundingBoxDimensions(width, height)" << endl;

	_boundingBox->setWidth(width);
	_boundingBox->setHeight(height);
}

Material* GameEntity::getTextureMaterial()
{
	cout << "GameEntity::getTextureMaterial()" << endl;

	if (!_textureMaterial)
		_textureMaterial = Material::generateMaterial(TEXTURE_VERTEX_SHADER_PATH, TEXTURE_PIXEL_SHADER_PATH);

	return _textureMaterial;
}

void GameEntity::draw() const
{
	cout << "GameEntity::draw()" << endl;

	_sprite->draw();
}
