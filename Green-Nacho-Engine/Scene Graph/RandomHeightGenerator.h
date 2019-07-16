#pragma once

#include <time.h>
#include <stdlib.h>
#include "Core/Exports.h"
#include "Core/EngineConstants.h"

namespace gn
{
	class ENGINE_DECL_SPEC RandomHeightGenerator
	{
	private:
		static int _seed;
		static int _rowRandomMultiplier;
		static int _columnRandomMultiplier;

		static int generateNoise(int row, int col);
		static int generateSmoothNoise(int row, int col);

	public:
		static void generateSeed();
		static int generateHeight(int row, int col);
	};
}