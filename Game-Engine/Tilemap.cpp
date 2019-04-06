#include "Tilemap.h"
#include "Texture.h"
#include "Material.h"
#include "Renderer.h"
#include "Window.h"

namespace gn
{
	unsigned int Tile::width = 0;
	unsigned int Tile::height = 0;

	Tilemap::Tilemap(Renderer* renderer, const std::string& tilesetPath, const std::string& levelPath, 
					int levelWidth, int levelHeight, int tileWidth, int tileHeight, 
					unsigned int tilesetRows, unsigned int tilesetColumns) : Entity(renderer),
	_levelWidth(levelWidth), _levelHeight(levelHeight), _accumTrans(glm::vec2(0.0f, 0.0f)),
	_texture(Texture::generateTextureBMP(tilesetPath)),
	_tiles(loadTiles(tilesetRows, tilesetColumns, tileWidth, tileHeight)),
	_vertexBufferData(NULL), _uvBufferData(NULL),
	_vertexBufferID(-1), _uvBufferID(-1)
	{
		std::cout << "Tilemap::Tilemap(tilesetPath, levelPath, levelWidth, levelHeight, tileWidth, tileHeight)" << std::endl;

		_material = Material::generateMaterial(TEXTURE_VERTEX_SHADER_PATH, TEXTURE_PIXEL_SHADER_PATH);
		_material->setTexture(_texture, "textureSampler");

		Tile::width = tileWidth;
		Tile::height = tileHeight;

		int windowWidth = _renderer->getRenderWindow()->getWidth();
		int windowHeight = _renderer->getRenderWindow()->getHeight();

		_lastRowOffset = windowHeight % tileHeight;
		_lastColumnOffset = windowWidth % tileWidth;
	
		_screenTilesRows = windowHeight / tileHeight + 1;
		_screenTilesColumns = windowWidth / tileWidth + 1;

		_level = loadLevelCSV(levelPath);
		_uvBufferData = createUvBuffer();
		_onScreenTiles = createOnScreenTiles();

		updateVerticesUV();
	}

	Tilemap::~Tilemap()
	{
		std::cout << "Tilemap::~Tilemap()" << std::endl;

		Texture::destroyTexture(_texture);
		Material::destroyMaterial(_material);
	
		for (int i = 0; i < _tilesRows; i++)
		{
			delete[] _tiles[i]->uvVertices;
			delete[] _tiles[i];
		}
		delete[] _tiles;
	
		for (int i = 0; i < _screenTilesRows; i++)
			delete[] _onScreenTiles[i];
		delete[] _onScreenTiles;

		for (int i = 0; i < _levelRows; i++)
			delete[] _level[i];
		delete[] _level;
	}

	int** Tilemap::loadLevelCSV(const std::string& levelPath)
	{
		try
		{
			std::ifstream levelFile;
			int** level;
			char buffer[LEVEL_LOAD_CHARS_BUFFER_SIZE];
			
			float rows = _levelHeight / Tile::height;
			float columns = _levelWidth / Tile::width;
			
			_levelRows = (_levelHeight % Tile::height == 0) ? rows : rows + 1;
			_levelColumns = (_levelWidth % Tile::width == 0) ? columns : columns + 1;
		
			level = new int*[_levelRows];
			for (int i = 0; i < _levelRows; i++)
				level[i] = new int[_levelColumns];	

			std::cout << "Opening the level file..." << std::endl;
			levelFile.open(levelPath, std::ios::in);
			if (!levelFile.good())
				throw std::ios::failure("The level file could not be opened.");

			levelFile.getline(buffer, LEVEL_LOAD_CHARS_BUFFER_SIZE);
			levelFile.get(buffer, LEVEL_LOAD_CHARS_BUFFER_SIZE, '>');
			levelFile.get();
			memset(buffer, 0, sizeof(buffer));

			int x = 0;
			int y = 0;
			int nextChar = levelFile.peek();

			while (isdigit(nextChar) && !levelFile.eof())
			{
				if (x < _levelColumns - 1)
					levelFile.get(buffer, LEVEL_LOAD_CHARS_BUFFER_SIZE, ',');
				else
				{
					if (y < _levelRows - 1)
						levelFile.get(buffer, LEVEL_LOAD_CHARS_BUFFER_SIZE, '\n');
					else
						levelFile.get(buffer, LEVEL_LOAD_CHARS_BUFFER_SIZE, '<');
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

			std::cout << "The level file was read properly." << std::endl;

			return level;
		}
		catch (std::iostream::failure& exception)
		{
			std::cerr << exception.what() << std::endl;
		}
	}

	Tile** Tilemap::loadTiles(unsigned int rows, unsigned int columns, int tileWidth, int tileHeight)
	{	
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
		Tile** onScreenTiles = new Tile*[_screenTilesRows];

		for (int i = 0; i < _screenTilesRows; i++)
			onScreenTiles[i] = new Tile[_screenTilesColumns];

		int totalTiles = _screenTilesRows * _screenTilesColumns;

		float vertexBufferSize = sizeof(float) * Tile::VERTEX_AMOUNT * Tile::VERTEX_COMPONENTS * totalTiles;

		_vertexBufferData = setScreenTilesVertices(totalTiles);
		_vertexBufferID = _renderer->generateVertexBuffer(_vertexBufferData, vertexBufferSize);

		return onScreenTiles;
	}

	float* Tilemap::setScreenTilesVertices(int totalTiles) const
	{
		float* vertexBufferData = new float[Tile::VERTEX_AMOUNT * Tile::VERTEX_COMPONENTS * totalTiles];

		int counter = 0;

		for (int y = 0; y < _screenTilesRows; y++)
			for (int x = 0; x < _screenTilesColumns; x++)
			{
				float minX = x * Tile::width;
				float maxX = x * Tile::width + Tile::width;
				float minY = (float)_renderer->getRenderWindow()->getHeight() - (float)(y * Tile::height + Tile::height);
				float maxY = (float)_renderer->getRenderWindow()->getHeight() - (float)(y * Tile::height);

				float vertices[Tile::VERTEX_AMOUNT * Tile::VERTEX_COMPONENTS] =
				{
					minX, minY, 0.0f,
					minX, maxY, 0.0f,
					maxX, maxY, 0.0f,
					maxX, minY, 0.0f
				};

				for (int i = 0; i < Tile::VERTEX_AMOUNT * Tile::VERTEX_COMPONENTS; i++, counter++)
					vertexBufferData[counter] = vertices[i];
			}

		return vertexBufferData;
	}

	float* Tilemap::createUvBuffer() const
	{
		int totalTiles = _screenTilesRows * _screenTilesColumns;

		float* uvBufferData = new float[Tile::VERTEX_AMOUNT * 2 * totalTiles];

		int counter = 0;

		float defaultUvVertices[8] =
		{
			0.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f
		};

		for (int y = 0; y < _screenTilesRows; y++)
			for (int x = 0; x < _screenTilesColumns; x++)
				for (int i = 0; i < Tile::VERTEX_AMOUNT * 2; i++, counter++)
					uvBufferData[counter] = defaultUvVertices[i];

		return uvBufferData;
	}

	void Tilemap::setTileProperty(unsigned int tileIndex, TileType tileType)
	{
		try
		{
			if (tileIndex > _tilesRows * _tilesColumns)
				throw std::logic_error("Could not set the tile property because the tile index is out of range.");
		
			unsigned int row = tileIndex / _tilesRows;
			unsigned int column = tileIndex % _tilesColumns;

			_tiles[row][column].tileType = tileType;

			glm::vec2 tilingOffset((int)_position.x / Tile::width, (int)_position.y / Tile::height);
			int lastRow = (int)_levelHeight / (int)Tile::height - 1;
			int lastColumn = (int)_levelWidth / (int)Tile::width - 1;

			for (int y = 0; y < _screenTilesRows; y++)
				for (int x = 0; x < _screenTilesColumns; x++)
				{
					int levelRow = glm::min(y + (int)tilingOffset.y, lastRow);
					int levelColumn = glm::min(x + (int)tilingOffset.x, lastColumn);
				
					if (_level[levelRow][levelColumn] == tileIndex)
						_onScreenTiles[y][x].tileType = tileType;
				}
		}
		catch (std::logic_error& exc)
		{
			std::cerr << exc.what() << std::endl;
		}
	}

	void Tilemap::updateVerticesUV()
	{
		int totalTiles = _screenTilesRows * _screenTilesColumns;
		int uvBufferSize = sizeof(float) * Tile::VERTEX_AMOUNT * 2 * totalTiles;

		glm::vec2 tilingOffset((int)_position.x / Tile::width, (int)_position.y / Tile::height);
		int lastRow = (int)_levelHeight / (int)Tile::height - 1;
		int lastColumn= (int)_levelWidth/ (int)Tile::width - 1;
	
		int counter = 0;
	
		for (int y = 0; y < _screenTilesRows; y++)
			for (int x = 0; x < _screenTilesColumns; x++)
			{
				int levelRow = glm::min(y + (int)tilingOffset.y, lastRow);
				int levelColumn = glm::min(x + (int)tilingOffset.x, lastColumn);

				Tile tile = getTile(_level[levelRow][levelColumn]);

				_onScreenTiles[y][x].tileType = tile.tileType;
				for (int i = 0; i < Tile::VERTEX_AMOUNT * 2; i++, counter++)
					_uvBufferData[counter] = tile.uvVertices[i];
			}

		_uvBufferID = _renderer->generateVertexBuffer(_uvBufferData, uvBufferSize);
	}

	void Tilemap::scrollView(float x, float y)
	{
		float screenOffsetX = _renderer->getRenderWindow()->getWidth();
		float screenOffsetY = _renderer->getRenderWindow()->getHeight();
		float translateX = 0.0f;
		float translateY = 0.0f;

		if (_position.x + _accumTrans.x + x < _levelWidth - screenOffsetX)
			translateX = (_position.x + _accumTrans.x + x > 0.0f) ? x : -(_position.x + _accumTrans.x);
		else
			translateX = _levelWidth - screenOffsetX - _position.x - _accumTrans.x;
	
		if (_position.y + _accumTrans.y + y < _levelHeight - screenOffsetY)
			translateY = (_position.y + _accumTrans.y + y > 0.0f) ? y : -(_position.y + _accumTrans.y);
		else
			translateY = _levelHeight - screenOffsetY - _position.y - _accumTrans.y;

		_accumTrans.x += translateX;
		_accumTrans.y += translateY;

		float accumTransX = abs(_accumTrans.x);
		float accumTransY = abs(_accumTrans.y);
	
		if (accumTransX >= Tile::width || accumTransY >= Tile::height)
		{
			if (accumTransX >= Tile::width)
			{
				translate(glm::sign(_accumTrans.x) * (int)Tile::width, 0.0f, 0.0f);
				_accumTrans.x -= glm::sign(_accumTrans.x) * (int)Tile::width;
			}

			if (accumTransY >= Tile::height)
			{
				translate(0.0f, glm::sign(_accumTrans.y) * (int)Tile::height, 0.0f);
				_accumTrans.y -= glm::sign(_accumTrans.y) * (int)Tile::width;
			}

			updateVerticesUV();
		}

		_renderer->updateView(_position.x + _accumTrans.x, _position.y + _accumTrans.y);
	}

	void Tilemap::dispose()
	{	
		if (_vertexBufferID != -1)
		{
			_renderer->destroyVertexBuffer(_vertexBufferID);
			delete _vertexBufferData;
			_vertexBufferData = NULL;
			_vertexBufferID = -1;
		}

		if (_uvBufferID != -1)
		{
			_renderer->destroyVertexBuffer(_uvBufferID);
			delete _uvBufferData;
			_uvBufferData = NULL;
			_uvBufferID = -1;
		}
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
		_renderer->drawBuffer(PrimitiveType::QUAD, Tile::VERTEX_AMOUNT * _screenTilesRows *_screenTilesColumns);
		_renderer->disableAttribute(0);
		_renderer->disableAttribute(1);

		_renderer->disableBlend();
	}

	Tile Tilemap::getTile(unsigned int tileIndex) const
	{
		try
		{
			if (tileIndex >= _tilesRows * _tilesColumns)
				throw std::logic_error("The tile index is out of the tileset range.");
		
			unsigned int column = tileIndex % _tilesColumns;
			unsigned int row = tileIndex / _tilesRows;

			return _tiles[row][column];
		}
		catch (std::logic_error& exc)
		{
			std::cerr << exc.what() << std::endl;
		}
	}

	TileType Tilemap::getTileType(unsigned int row, unsigned int column) const
	{
		try
		{
			if (row >= _levelRows || (int)row < 0 || column >= _levelColumns || (int)column < 0)
				throw std::logic_error("The tile that is trying to be accessed is out of the level boundaries.");
		
			return getTile(_level[row][column]).tileType;
		}
		catch (std::logic_error& exc)
		{
			std::cerr << exc.what() << std::endl;
		}
	}

	glm::vec2 Tilemap::worldToGrid(float posX, float posY) const
	{
		unsigned int row = (_levelRows - 1) - (int)posY / Tile::height;
		unsigned int col = posX / Tile::width;

		return glm::vec2(row, col);
	}

	glm::vec2 Tilemap::gridToWorld(unsigned int row, unsigned int col) const
	{
		float posX = col * Tile::width;
		float posY = -((int)(row - _levelRows + 1) * (int)Tile::height) + _lastRowOffset;

		return glm::vec2(posX, posY);
	}
}