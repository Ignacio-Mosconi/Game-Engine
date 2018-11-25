#include "Tilemap.h"
#include "Texture.h"
#include "Material.h"

Tilemap::Tilemap(const string& tilesetPath, const string& levelPath, int levelWidth, int levelHeight, int tileWidth, int tileHeight) : 
_tileset(Texture::generateTextureBMP(tilesetPath)), _level(loadLevelCSV(levelPath, levelWidth, levelHeight, tileWidth, tileHeight))
{
	cout << "Tilemap::Tilemap(tilesetPath, levelPath, levelWidth, levelHeight, tileWidth, tileHeight)";

	_material = Material::generateMaterial(TEXTURE_VERTEX_SHADER_PATH, TEXTURE_PIXEL_SHADER_PATH);
	_material->setTexture(_tileset, "textureSmapler");
}

Tilemap::~Tilemap()
{
	cout << "Tilemap::~Tilemap()" << endl;

	Texture::destroyTexture(_tileset);
	Material::destroyMaterial(_material);
	
	delete[] _level;
}

int** Tilemap::loadLevelCSV(const string& levelPath, int levelWidth, int levelHeight, int tileWidth, int tileHeight)
{
	cout << "Tilemap::loadLevelCSV(levelPath, levelWidth, levelHeight, tileWidth, tileHeight)";

	try
	{
		ifstream levelFile;
		int** level;
		char buffer[CHARS_BUFFER_SIZE];
		unsigned int mapRows = (levelHeight % tileHeight == 0) ? levelHeight / tileHeight : levelHeight / tileHeight + 1;
		unsigned int mapColumns = (levelWidth % tileWidth == 0) ? levelWidth / tileWidth : levelWidth / tileWidth + 1;
		
		level = new int*[mapRows];
		for (int i = 0; i < mapRows; i++)
			level[i] = new int[mapColumns];	

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
			if (x < mapColumns - 1)
				levelFile.get(buffer, CHARS_BUFFER_SIZE, ',');
			else
			{
				if (y < mapRows - 1)
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
			
			if (x < mapColumns - 1)
				x++;
			else
			{
				x = 0;
				y++;
				cout << endl;
			}
			levelFile.get();
			nextChar = levelFile.peek();
		}

		return level;
	}
	catch (iostream::failure& exception)
	{
		cerr << exception.what() << endl;
	}
}