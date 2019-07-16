#include "Scene Graph/RandomHeightGenerator.h"

namespace gn
{
	int RandomHeightGenerator::_seed = 0;
	int RandomHeightGenerator::_rowRandomMultiplier = 0;
	int RandomHeightGenerator::_columnRandomMultiplier = 0;

	int RandomHeightGenerator::generateNoise(int row, int col)
	{
		int noise;

		int noiseSeed = row * _rowRandomMultiplier + col * _columnRandomMultiplier + _seed;
		srand(noiseSeed);
		noise = rand() % (int)MAX_BYTE_VALUE;
		srand(_seed);

		return noise;
	}

	int RandomHeightGenerator::generateSmoothNoise(int row, int col)
	{
		int smoothNoise;
		
		int corners = (generateNoise(row - 1, col - 1) + generateNoise(row - 1, col + 1) +
						generateNoise(row + 1, col - 1) + generateNoise(row + 1, col + 1)) / 16;		
		int sides = (generateNoise(row, col - 1) + generateNoise(row, col + 1) +
						generateNoise(row - 1, col) + generateNoise(row + 1, col)) / 8;
		int center = generateNoise(row, col) / 4;

		smoothNoise = corners + sides + center;

		return smoothNoise;
	}

	void RandomHeightGenerator::generateSeed()
	{
		_seed = (int)time(0);
		srand(_seed);

		_rowRandomMultiplier = rand();
		_columnRandomMultiplier = rand();
	}

	int RandomHeightGenerator::generateHeight(int row, int col)
	{
		return generateSmoothNoise(row, col);
	}
}