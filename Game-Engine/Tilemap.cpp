#include "Tilemap.h"
#include "Texture.h"
#include "Material.h"
#include "Renderer.h"
#include "Window.h"

unsigned int Tile::tileWidth = 0;
unsigned int Tile::tileHeight = 0;

Tilemap::Tilemap(Renderer* renderer, const string& tilesetPath, const string& levelPath, 
				int levelWidth, int levelHeight, int tileWidth, int tileHeight, 
				unsigned int tilesetRows, unsigned int tilesetColumns) : Entity(renderer),
_levelWidth(levelWidth), _levelHeight(levelHeight),
_texture(Texture::generateTextureBMP(tilesetPath)), _tiles(loadTiles(tilesetRows, tilesetColumns, tileWidth, tileHeight)),
_vertexBufferData(NULL), _uvBufferData(NULL),
_vertexBufferID(-1), _uvBufferID(-1)
{
	cout << "Tilemap::Tilemap(tilesetPath, levelPath, levelWidth, levelHeight, tileWidth, tileHeight)" << endl;

	_material = Material::generateMaterial(TEXTURE_VERTEX_SHADER_PATH, TEXTURE_PIXEL_SHADER_PATH);
	_material->setTexture(_texture, "textureSampler");

	Tile::tileWidth = tileWidth;
	Tile::tileHeight = tileHeight;

	int windowWidth = _renderer->getRenderWindow()->getWidth();
	int windowHeight = _renderer->getRenderWindow()->getHeight();

	_onScreenTilesRows = (windowHeight % tileHeight == 0) ? windowHeight / tileHeight : windowHeight / tileHeight + 1;
	_onScreenTilesColumns = (windowWidth % tileWidth == 0) ? windowWidth / tileWidth : windowWidth / tileWidth + 1;

	_level = loadLevelCSV(levelPath);
	_uvBufferData = createUvBuffer();
	_onScreenTiles = createOnScreenTiles();

	updateVerticesUV();
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
		_levelRows = (_levelHeight % Tile::tileHeight == 0) ? _levelHeight / Tile::tileHeight : _levelHeight / Tile::tileHeight + 1;
		_levelColumns = (_levelWidth % Tile::tileWidth == 0) ? _levelWidth / Tile::tileWidth : _levelWidth / Tile::tileWidth + 1;
		
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

Tile** Tilemap::loadTiles(unsigned int rows, unsigned int columns, int tileWidth, int tileHeight)
{	
	cout << "Tilemap::loadTiles(rows, columns)" << endl;

	_tilesRows = rows;
	_tilesColumns = columns;

	Tile** tiles = new Tile*[_tilesRows];
	
	for (int i = 0; i < _tilesRows; i++)
		tiles[i] = new Tile[_tilesColumns];
	
	for (int y = 0; y < _tilesRows; y++)
		for (int x = 0; x < _tilesColumns; x++)
		{
			float minU = (float)(x * tileWidth) / (float)_texture->getWidth();
			float maxU = (float)(x * tileWidth + tileWidth) / (float)_texture->getWidth();
			float minV = 1.0f - (float)(y * tileHeight + tileHeight) / (float)_texture->getHeight();
			float maxV = 1.0f - (float)(y * tileHeight) / (float)_texture->getHeight();

			float* uvVertices = new float[8]
			{
				minU, minV,
				minU, maxV,
				maxU, maxV,
				maxU, minV
			};

			tiles[y][x].uvVertices = uvVertices;
		}

	return tiles;
}

Tile** Tilemap::createOnScreenTiles()
{
	cout << "Tilemap::createOnScreenTiles()" << endl;

	Tile** onScreenTiles = new Tile*[_onScreenTilesRows];

	for (int i = 0; i < _onScreenTilesRows; i++)
		onScreenTiles[i] = new Tile[_onScreenTilesColumns];

	int totalTiles = _onScreenTilesRows * _onScreenTilesColumns;

	float vertexBufferSize = sizeof(float) * Tile::vertexAmount * Tile::vertexComponents * totalTiles;

	_vertexBufferData = setOnScreenTilesVertices(totalTiles);
	_vertexBufferID = _renderer->generateVertexBuffer(_vertexBufferData, vertexBufferSize);

	return onScreenTiles;
}

float* Tilemap::setOnScreenTilesVertices(int totalTiles) const
{
	cout << "Tilemap::setOnScreenTilesVerices(int totalTiles)" << endl;

	float* vertexBufferData = new float[Tile::vertexAmount * Tile::vertexComponents * totalTiles];

	int counter = 0;

	for (int y = 0; y < _onScreenTilesRows; y++)
		for (int x = 0; x < _onScreenTilesColumns; x++)
		{
			float minX = x * Tile::tileWidth;
			float maxX = x * Tile::tileWidth + Tile::tileWidth;
			float minY = (float)_renderer->getRenderWindow()->getHeight() - (float)(y * Tile::tileHeight + Tile::tileHeight);
			float maxY = (float)_renderer->getRenderWindow()->getHeight() - (float)(y * Tile::tileHeight);

			float vertices[Tile::vertexAmount * Tile::vertexComponents] =
			{
				minX, minY, 0.0f,
				minX, maxY, 0.0f,
				maxX, maxY, 0.0f,
				maxX, minY, 0.0f
			};

			for (int i = 0; i < Tile::vertexAmount * Tile::vertexComponents; i++, counter++)
				vertexBufferData[counter] = vertices[i];
		}
	
	return vertexBufferData;
}

float* Tilemap::createUvBuffer() const
{
	cout << "Tilemap::createUVBuffer()" << endl;

	int totalTiles = _onScreenTilesRows * _onScreenTilesColumns;

	float* uvBufferData = new float[Tile::vertexAmount * 2 * totalTiles];

	int counter = 0;

	float defaultUvVertices[8] =
	{
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f
	};

	for (int y = 0; y < _onScreenTilesRows; y++)
		for (int x = 0; x < _onScreenTilesColumns; x++)
			for (int i = 0; i < Tile::vertexAmount * 2; i++, counter++)
				uvBufferData[counter] = defaultUvVertices[i];

	return uvBufferData;
}

Tile Tilemap::getTile(unsigned int tileIndex) const
{
	cout << "Tilemap::getTile(tileIndex)" << endl;

	unsigned int column = tileIndex % _tilesColumns;
	unsigned int row = tileIndex / _tilesRows;

	return _tiles[row][column];
}

void Tilemap::setTileProperty(unsigned int tileIndex, TileType tileType)
{
	cout << "Tilemap::setTileProperty(tileIndex, tileType)" << endl;

	unsigned int row = tileIndex / _tilesRows;
	unsigned int column = tileIndex % _tilesColumns;
	
	_tiles[row][column].tileType = tileType;
}

void Tilemap::updateVerticesUV()
{
	cout << "Tilemap::updateVerticesUV()" << endl;

	int totalTiles = _onScreenTilesRows * _onScreenTilesColumns;
	int uvBufferSize = sizeof(float) * Tile::vertexAmount * 2 * totalTiles;

	int counter = 0;

	for (int y = 0; y < _onScreenTilesRows; y++)
		for (int x = 0; x < _onScreenTilesColumns; x++)
		{
			Tile tile = getTile(_level[y][x]);

			for (int i = 0; i < Tile::vertexAmount * 2; i++, counter++)
				_uvBufferData[counter] = tile.uvVertices[i];
		}

	_uvBufferID = _renderer->generateVertexBuffer(_uvBufferData, uvBufferSize);
}

void Tilemap::draw() const
{
	cout << "Tilemap::draw()" << endl;

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
	_renderer->drawBuffer(QUAD, Tile::vertexAmount * _onScreenTilesRows *_onScreenTilesColumns);
	_renderer->disableAttribute(0);
	_renderer->disableAttribute(1);

	_renderer->disableBlend();
}

vec2 Tilemap::worldToGrid(float posX, float posY) const
{
	cout << "Tilemap::draw()" << endl;

	unsigned int row = (posY - _renderer->getCameraPosition().y) / Tile::tileHeight;
	unsigned int col = (posX - _renderer->getCameraPosition().x) / Tile::tileWidth;

	return vec2(row, col);
}

vec2 Tilemap::gridToWorld(unsigned int row, unsigned int col) const
{
	cout << "Tilemap::draw()" << endl;

	float posX = col * Tile::tileWidth + _renderer->getCameraPosition().x;
	float posY = row * Tile::tileHeight + _renderer->getCameraPosition().y;

	return vec2(posX, posY);
}