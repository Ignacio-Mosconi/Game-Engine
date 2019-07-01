#pragma once

#include <iostream>
#include <fstream>
#include <glm/vec2.hpp>
#include <glm/gtx/common.hpp>
#include "Legacy/Entity.h"
#include "Core/EngineConstants.h"
#include "Core/Enums.h"

namespace gn
{
	class Texture;
	class Material;

	namespace legacy
	{
		struct Tile
		{
			static const int VERTEX_AMOUNT = 4;
			static const int VERTEX_COMPONENTS = 3;

			static unsigned int width;
			static unsigned int height;

			TileType tileType;
			float* uvVertices;
		};

		class ENGINE_DECL_SPEC Tilemap : public Entity
		{
		private:
			Texture* _texture;
			Material* _material;

			Tile** _tiles;
			Tile** _onScreenTiles;
			int** _level;

			float* _vertexBufferData;
			float* _uvBufferData;
			unsigned int _vertexBufferID;
			unsigned int _uvBufferID;

			unsigned int _levelWidth;
			unsigned int _levelHeight;

			unsigned int _tilesRows;
			unsigned int _tilesColumns;

			unsigned int _screenTilesRows;
			unsigned int _screenTilesColumns;

			unsigned int _levelRows;
			unsigned int _levelColumns;

			float _lastRowOffset;
			float _lastColumnOffset;

			glm::vec2 _accumTrans;

			int** loadLevelCSV(const std::string& levelPath);
			Tile** loadTiles(unsigned int rows, unsigned int columns, int tileWidth, int tileHeight);

			Tile** createOnScreenTiles();

			float* setScreenTilesVertices(int totalTiles) const;
			float* createUvBuffer() const;

		public:
			Tilemap(Renderer* renderer, const std::string& tilesetPath, const std::string& levelPath,
				int levelWidth, int levelHeight, int tileWidth, int tileHeight, unsigned int tilesetRows, unsigned int tilesetColumns);
			~Tilemap();

			void setTileProperty(unsigned int tyleIndex, TileType tileType);

			void updateVerticesUV();

			void scrollView(float x, float y);

			void dispose();

			void draw() const;

			Tile getTile(unsigned int tileIndex) const;
			TileType getTileType(unsigned int row, unsigned int column) const;

			glm::vec2 worldToGrid(float posX, float posY) const;
			glm::vec2 gridToWorld(unsigned int row, unsigned int col) const;

			float getLastRowOffset() const { return _lastRowOffset; }
			float getLastColumnOffset() const { return _lastColumnOffset; }
		};
	}
}