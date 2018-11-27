#include "GameEntity.h"
#include "Sprite.h"
#include "BoundingBox.h"
#include "Renderer.h"
#include "Material.h"
#include "Texture.h"
#include "CollisionManager.h"
#include "Animation.h"

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