#include "GameEntity.h"
#include "Sprite.h"
#include "BoundingBox.h"
#include "Renderer.h"
#include "Material.h"
#include "Texture.h"

Material* GameEntity::_textureMaterial = NULL;

GameEntity::GameEntity(Renderer* renderer, string& imagePath) : _sprite(createSprite(renderer, imagePath))
{
	if (_sprite)
		_sprite->setPosition(0, 0, 0);
	
	float bbWidth = (float)(_sprite->getMaterial()->getTextureWidth());
	float bbHeight = (float)(_sprite->getMaterial()->getTextureHeight());

	_boundingBox = new BoundingBox(bbWidth, bbHeight);
}

GameEntity::GameEntity(Renderer* renderer, string& imagePath, float x, float y) : _sprite(createSprite(renderer, imagePath))
{
	if (_sprite)
		_sprite->setPosition(x, y, 0);

	float bbWidth = (float)(_sprite->getMaterial()->getTextureWidth());
	float bbHeight = (float)(_sprite->getMaterial()->getTextureHeight());

	_boundingBox = new BoundingBox(bbWidth, bbHeight);
}

GameEntity::~GameEntity()
{
	delete _sprite;
	delete _boundingBox;
	if (_textureMaterial)
		Material::destroyMaterial(_textureMaterial);
	if (_texture)
		Texture::destroyTexture(_texture);
}

Sprite* GameEntity::createSprite(Renderer* renderer, string& imagePath)
{
	_texture = Texture::generateTextureBMP(imagePath);
	_textureMaterial->setTexture(_texture, "textureSampler");
	_sprite = new Sprite(renderer, _textureMaterial);

	return _sprite;
}

void GameEntity::setBoundingBoxDimensions(float width, float height)
{
	_boundingBox->setWidth(width);
	_boundingBox->setHeight(height);
}

Material* GameEntity::getTextureMaterial()
{
	if (!_textureMaterial)
		_textureMaterial = Material::generateMaterial(TEXTURE_VERTEX_SHADER_PATH, TEXTURE_PIXEL_SHADER_PATH);

	return _textureMaterial;
}
