#include "Tilemap.h"
#include "Texture.h"
#include "Material.h"
#include "Renderer.h"
#include "Window.h"

Tilemap::Tilemap(Renderer* renderer, const string& tilesetPath, const string& levelPath, 
				int levelWidth, int levelHeight, int tileWidth, int tileHeight, 
				unsigned int tilesetRows, unsigned int tilesetColumns) : Entity(renderer),
_texture(Texture::generateTextureBMP(tilesetPath)), _tiles(loadTiles(tilesetRows, tilesetColumns)),
_levelWidth(levelWidth), _levelHeight(levelHeight), _tileWidth(tileWidth), _tileHeight(tileHeight)
{
	cout << "Tilemap::Tilemap(tilesetPath, levelPath, levelWidth, levelHeight, tileWidth, tileHeight)" << endl;

	_material = Material::generateMaterial(TEXTURE_VERTEX_SHADER_PATH, TEXTURE_PIXEL_SHADER_PATH);
	_material->setTexture(_texture, "textureSampler");

	int windowWidth = _renderer->getRenderWindow()->getWidth();
	int windowHeight = _renderer->getRenderWindow()->getHeight();

	_onScreenTilesRows = (windowHeight % _tileHeight == 0) ? windowHeight / _tileHeight : windowHeight / _tileHeight + 1;
	_onScreenTilesColumns = (windowWidth % _tileWidth == 0) ? windowWidth / _tileWidth : windowWidth / _tileWidth + 1;
	
	_level = loadLevelCSV(levelPath);
	_onScreenTiles = createOnScreenTiles();
}

Tilemap::~Tilemap()
{
	cout << "Tilemap::~Tilemap()" << endl;

	Texture::destroyTexture(_texture);
	Material::destroyMaterial(_material);
	
	for (int i = 0; i < _tilesRows; i++)
	{
		delete[] _tiles[i]->uvVertices;
		delete[] _tiles[i];
	}
	delete[] _tiles;
	
	for (int i = 0; i < _onScreenTilesRows; i++)
		delete[] _onScreenTiles[i];
	delete[] _onScreenTiles;

	for (int i = 0; i < _levelRows; i++)
		delete[] _level[i];
	delete[] _level;
}

int** Tilemap::loadLevelCSV(const string& levelPath)
{
	cout << "Tilemap::loadLevelCSV(levelPath)" << endl;

	try
	{
		ifstream levelFile;
		int** level;
		char buffer[CHARS_BUFFER_SIZE];
		_levelRows = (_levelHeight % _tileHeight == 0) ? _levelHeight / _tileHeight : _levelHeight / _tileHeight + 1;
		_levelColumns = (_levelWidth % _tileWidth == 0) ? _levelWidth / _tileWidth : _levelWidth / _tileWidth + 1;
		
		level = new int*[_levelRows];
		for (int i = 0; i < _levelRows; i++)
			level[i] = new int[_levelColumns];	

		cout << "Opening the level file..." << endl;
		levelFile.open(levelPath, ios::in);
		if (!levelFile.good())
			throw ios::failure("The level file could not be opened.");

		levelFile.getline(buffer, CHARS_BUFFER_SIZE);
		levelFile.get(buffer, CHARS_BUFFER_SIZE, '>');
		levelFile.get();
		memset(buffer, 0, sizeof(buffer));

		int x = 0;
		int y = 0;
		int nextChar = levelFile.peek();

		while (isdigit(nextChar) && !levelFile.eof())
		{
			if (x < _levelColumns - 1)
				levelFile.get(buffer, CHARS_BUFFER_SIZE, ',');
			else
			{
				if (y < _levelRows - 1)
					levelFile.get(buffer, CHARS_BUFFER_SIZE, '\n');
				else
					levelFile.get(buffer, CHARS_BUFFER_SIZE, '<');
			}
			
			int digits = 0;
			int value = 0;
			
			for (int i = 0; buffer[i] != '\0'; i++)
				digits++;
			for (int i = 0; i < digits; i++)
				value += ((int)buffer[i] - (int)'0') * pow(10, digits - 1 - i);

			level[y][x] = value;
			
			if (x < _levelColumns - 1)
				x++;
			else
			{
				x = 0;
				y++;
			}
			levelFile.get();
			nextChar = levelFile.peek();
		}

		cout << "The level file was read properly." << endl;

		return level;
	}
	catch (iostream::failure& exception)
	{
		cerr << exception.what() << endl;
	}
}

Tile** Tilemap::loadTiles(unsigned int rows, unsigned int columns)
{	
	cout << "Tilemap::loadTiles(rows, columns)" << endl;

	_tilesRows = rows;
	_tilesColumns = columns;

	Tile** tiles = new Tile*[_tilesRows];
	
	for (int i = 0; i < _tilesRows; i++)
		tiles[i] = new Tile[_tilesColumns];

	int totalTiles = _tilesRows * _tilesColumns;
	float uvBufferSize = sizeof(float) * Tile::vertices * 2 * totalTiles;
	_uvBufferData = new float[Tile::vertices * 2 * totalTiles];

	int counter = 0;
	
	for (int y = 0; y < _tilesRows; y++)
		for (int x = 0; x < _tilesColumns; x++)
		{
			float minU = (float)(x * _tileWidth) / (float)_texture->getWidth();
			float maxU = (float)(x * _tileWidth + _tileWidth) / (float)_texture->getWidth();
			float minV = 1.0f - (float)(y * _tileHeight + _tileHeight) / (float)_texture->getHeight();
			float maxV = 1.0f - (float)(y * _tileHeight) / (float)_texture->getHeight();

			float* uvVertices = new float[8]
			{
				minU, maxV,
				maxU, maxV,
				minU, minV,
				maxU, minV
			};

			tiles[y][x].uvVertices = uvVertices;

			for (int i = 0; i < Tile::vertices * 2; i++, counter++)
				_uvBufferData[counter] = uvVertices[i];
		}

	_uvBufferID = _renderer->generateVertexBuffer(_uvBufferData, uvBufferSize);

	return tiles;
}

Tile** Tilemap::createOnScreenTiles()
{
	cout << "Tilemap::createOnScreenTiles()" << endl;

	Tile** onScreenTiles = new Tile*[_onScreenTilesRows];

	for (int i = 0; i < _onScreenTilesRows; i++)
		onScreenTiles[i] = new Tile[_onScreenTilesColumns];

	int totalTiles = _onScreenTilesRows * _onScreenTilesColumns;

	float vertexBufferSize = sizeof(float) * Tile::vertices * Tile::vertexComponents * totalTiles;

	_vertexBufferData = setOnScreenTilesVertices(totalTiles);
	_vertexBufferID = _renderer->generateVertexBuffer(_vertexBufferData, vertexBufferSize);

	return onScreenTiles;
}

float* Tilemap::setOnScreenTilesVertices(int totalTiles) const
{
	float* vertexBufferData = new float[Tile::vertices * Tile::vertexComponents * totalTiles];

	int counter = 0;

	for (int y = 0; y < _onScreenTilesRows; y++)
		for (int x = 0; x < _onScreenTilesColumns; x++)
		{
			float minX = x * _tileWidth;
			float maxX = x * _tileWidth + _tileWidth;
			float minY = _renderer->getRenderWindow()->getHeight() - (float)(y * _tileHeight + _tileHeight);
			float maxY = _renderer->getRenderWindow()->getHeight() - y * _tileHeight;

			float vertices[Tile::vertices * Tile::vertexComponents] =
			{
				minX, maxY, 0.0f,
				maxX, maxY, 0.0f,
				minX, minY, 0.0f,
				maxX, minY, 0.0f
			};

			for (int i = 0; i < Tile::vertices * Tile::vertexComponents; i++, counter++)
				vertexBufferData[counter] = vertices[i];
		}
	
	return vertexBufferData;
}

void Tilemap::updateVerticesUV()
{
	int totalTiles = _tilesRows * _tilesColumns;
	int uvBufferSize = sizeof(float) * Tile::vertices * 2 * totalTiles;

	int counter = 0;

	for (int y = 0; y < _onScreenTilesRows; y++)
		for (int x = 0; x < _onScreenTilesColumns; x++)
		{
			Tile tile = getTile(_level[y][x]);
			for (int i = 0; i < Tile::vertices * 2; i++, counter++)
				_vertexBufferData[counter] = tile.uvVertices[i];
		}

	_vertexBufferID = _renderer->generateVertexBuffer(_uvBufferData, uvBufferSize);
}

Tile Tilemap::getTile(unsigned int tileIndex) const
{
	unsigned int column = tileIndex % _tilesColumns;
	unsigned int row = tileIndex / _tilesRows;

	return _tiles[row][column];
}

void Tilemap::draw() const
{
	_renderer->loadIdentityMatrix();
	_renderer->setModelMatrix(_modelMatrix);

	_material->bind();
	_material->setMatrixProperty("MVP", _renderer->getMVP());
	_material->bindTexture();

	_renderer->enableBlend();

	_renderer->enableAttribute(0);
	_renderer->enableAttribute(1);
	_renderer->bindBuffer(0, 3, _vertexBufferID);
	_renderer->bindBuffer(1, 2, _uvBufferID);
	_renderer->drawBuffer(TRIANGLE_STRIP, Tile::vertices);
	_renderer->disableAttribute(0);
	_renderer->disableAttribute(1);

	_renderer->disableBlend();
}