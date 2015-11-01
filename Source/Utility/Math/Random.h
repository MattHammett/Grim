#ifndef RANDOM_H
#define RANDOM_H

#include "../Type.h"
#include <random>
#include <assert.h>

namespace Grim
{
	class Random
	{
	public:
		static void seed(uint32 seed = 0);
		static int32 between(int32 min, int32 max);
		static float32 between(float32 min, float32 max);
	private:
		static std::mt19937 m_Engine;
		static std::random_device m_RandomDevice;
	};
}

#endif